/*
** rectangle.cpp - rectangle widget implementation
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

#include "../rectangle.h"
#include "../../form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::rectangle::rectangle_specs::operator==(const rectangle_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(color_border == param.color_border);
		}

		bool widgets::rectangle::rectangle_specs::operator!=(const rectangle_specs& param) {
			return !operator==(param);
		}

		class widgets::rectangle::impl {
		public:
			impl(containers::page& page, const std::string& alias) :
				page_(page),
				specs_(page_.d_page_.add_rectangle(alias)) {}
			containers::page& page_;
			rectangle_specs& specs_;
		};

		widgets::rectangle::rectangle(containers::page& page, const std::string& alias) :
			d_(*(new impl(page, alias))) {}

		widgets::rectangle::~rectangle() { delete& d_; }

		widgets::rectangle::rectangle_specs&
			widgets::rectangle::specs() {
			return d_.specs_;
		}

		widgets::rectangle::rectangle_specs&
			widgets::rectangle::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				auto& page = fm.d_.p_pages_.at(page_alias);
				auto results = fm.d_.find_widget(page, path_remaining);
				return results.page.d_page_.get_rectangle(results.widget.alias()).specs();
			}

			throw std::invalid_argument("Invalid path");
		}
	}
}
