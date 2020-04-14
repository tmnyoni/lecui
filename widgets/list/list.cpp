/*
** list.cpp - list widget implementation
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

#include "../list.h"
#include "../../form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::list_specs::operator==(const list_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(color_border == param.color_border) &&
				(color_dropdown_hot == param.color_dropdown_hot) &&
				(color_menu == param.color_menu) &&
				(color_grid == param.color_grid) &&
				(color_text_header == param.color_text_header) &&
				(color_fill_header == param.color_fill_header) &&
				(color_fill_alternate == param.color_fill_alternate) &&
				(color_row_hot == param.color_row_hot) &&
				(color_row_selected == param.color_row_selected);
		}

		bool widgets::list_specs::operator!=(const list_specs& param) {
			return !operator==(param);
		}

		class widgets::list::impl {
		public:
			impl(containers::page& page) :
				page_(page) {}
			containers::page& page_;
		};

		widgets::list::list(containers::page& page) :
			d_(*(new impl(page))) {}

		widgets::list::~list() { delete& d_; }

		widgets::list_specs&
			widgets::list::add(const std::string& alias) {
			return d_.page_.d_page_.add_list(alias);
		}

		widgets::list_specs&
			widgets::list::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				auto& page = fm.d_.p_pages_.at(page_alias);
				auto results = fm.d_.find_widget(page, path_remaining);
				return results.page.d_page_.get_list(results.widget.alias()).specs();
			}

			throw std::invalid_argument("Invalid path");
		}
	}
}
