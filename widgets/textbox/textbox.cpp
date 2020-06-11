/*
** textbox.cpp - textbox widget implementation
**
** lecui user interface library
** Copyright (c) 2019 Alec T. Musasa (alecmus at live dot com)
**
*******************************************************************************
** This file is part of the liblec library which is released under the Creative
** Commons Attribution Non-Commercial 2.0 license (CC-BY-NC 2.0). See the file
** LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
** for full license details.
*/

#include "../textbox.h"
#include "../passwordbox.h"
#include "../../form_impl/form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::textbox::textbox_specs::operator==(const textbox_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(color_border == param.color_border) &&
				(color_prompt == param.color_prompt) &&
				(color_caret == param.color_caret);
		}

		bool widgets::textbox::textbox_specs::operator!=(const textbox_specs& param) {
			return !operator==(param);
		}

		class widgets::textbox::impl {
		public:
			impl(containers::page& page, const std::string& alias) :
				page_(page),
				specs_(page_.d_page_.add_textbox(alias)) {
				specs_.color_text = defaults::color(page_.d_page_.fm_.d_.theme_, item::label);
				specs_.color_prompt = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox_prompt);
				specs_.color_fill = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox);
				specs_.color_border = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox_border);
				specs_.color_disabled = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox_disabled);
				specs_.color_selected = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox_selected);
				specs_.color_caret = defaults::color(page_.d_page_.fm_.d_.theme_, item::textbox_caret);
			}
			containers::page& page_;
			textbox_specs& specs_;
		};

		widgets::textbox::textbox(containers::page& page, const std::string& alias) :
			d_(*(new impl(page, alias))) {}

		widgets::textbox::~textbox() { delete& d_; }

		widgets::textbox::textbox_specs&
			widgets::textbox::specs() {
			return d_.specs_;
		}

		widgets::textbox::textbox_specs&
			widgets::textbox::operator()() {
			return specs();
		}

		widgets::textbox::textbox_specs&
			widgets::textbox::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				try {
					// check form pages
					auto& page = fm.d_.p_pages_.at(page_alias);
					auto results = fm.d_.find_widget(page, path_remaining);
					return results.page.d_page_.get_textbox(results.widget.alias()).specs();
				}
				catch (const std::exception&) {}
				try {
					// check status panes
					auto& page = fm.d_.p_status_panes_.at(page_alias);
					auto results = fm.d_.find_widget(page, path_remaining);
					return results.page.d_page_.get_textbox(results.widget.alias()).specs();
				}
				catch (const std::exception&) {}
			}

			throw std::invalid_argument("Invalid path");
		}

		widgets::passwordbox::passwordbox(containers::page& page, const std::string& alias) :
			textbox(page, alias) {
			d_.specs_.mask = '�';
			d_.specs_.prompt = "Enter password here";
		}

		widgets::passwordbox::~passwordbox() {}
	}
}
