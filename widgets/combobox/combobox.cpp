//
// combobox.cpp - combobox widget implementation
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#include "../combobox.h"
#include "../../form_impl/form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::combobox::combobox_specs::operator==(const combobox_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(editable == param.editable) &&
				(color_border == param.color_border) &&
				(color_fill_editable == param.color_fill_editable) &&
				(color_caret == param.color_caret) &&
				(color_dropdown == param.color_dropdown) &&
				(color_dropdown_hot == param.color_dropdown_hot) &&
				(color_dropdown_arrow == param.color_dropdown_arrow) &&
				(color_dropdown_arrow_hot == param.color_dropdown_arrow_hot);
		}

		bool widgets::combobox::combobox_specs::operator!=(const combobox_specs& param) {
			return !operator==(param);
		}

		class widgets::combobox::combobox_impl {
		public:
			combobox_impl(containers::page& page, const std::string& alias) :
				page_(page),
				specs_(page_.d_page_.add_combobox(alias)) {
				specs_.color_text = defaults::color(page_.d_page_.fm_.d_.theme_, item::label);
				specs_.color_fill = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox);
				specs_.color_fill_editable = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_editable);
				specs_.color_caret = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_caret);
				specs_.color_border = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_border);
				specs_.color_hot = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_hover);
				specs_.color_selected = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_selected);
				specs_.color_dropdown = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_dropdown);
				specs_.color_dropdown_hot = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_dropdown_hot);
				specs_.color_dropdown_arrow = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_dropdown_arrow);
				specs_.color_dropdown_arrow_hot = defaults::color(page_.d_page_.fm_.d_.theme_, item::combobox_dropdown_arrow_hot);
			}
			containers::page& page_;
			combobox_specs& specs_;
		};

		widgets::combobox::combobox(containers::page& page) :
			combobox(page, "") {}

		widgets::combobox::combobox(containers::page& page, const std::string& alias) :
			d_(*(new combobox_impl(page, alias))) {}

		widgets::combobox::~combobox() { delete& d_; }

		widgets::combobox::combobox_specs&
			widgets::combobox::specs() {
			return d_.specs_;
		}

		widgets::combobox::combobox_specs&
			widgets::combobox::operator()() {
			return specs();
		}

		widgets::combobox::combobox_specs&
			widgets::combobox::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				try {
					// check form pages
					auto& page = fm.d_.p_pages_.at(page_alias);
					auto results = fm.d_.find_widget(page, path_remaining);
					return results.page.d_page_.get_combobox(results.widget.alias()).specs();
				}
				catch (const std::exception&) {}
				try {
					// check status panes
					auto& page = fm.d_.p_status_panes_.at(page_alias);
					auto results = fm.d_.find_widget(page, path_remaining);
					return results.page.d_page_.get_combobox(results.widget.alias()).specs();
				}
				catch (const std::exception&) {}
			}

			throw std::invalid_argument("Invalid path");
		}
	}
}
