/*
** progress_indicator.cpp - progress indicator widget implementation
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

#include "../progress_indicator.h"
#include "../../form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::progress_indicator::progress_indicator_specs::operator==(const progress_indicator_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(color_empty == param.color_empty);
		}

		bool widgets::progress_indicator::progress_indicator_specs::operator!=(const progress_indicator_specs& param) {
			return !operator==(param);
		}

		class widgets::progress_indicator::impl {
		public:
			impl(containers::page& page, const std::string& alias) :
				page_(page),
				specs_(page_.d_page_.add_progress_indicator(alias)) {}
			containers::page& page_;
			progress_indicator_specs& specs_;
		};

		widgets::progress_indicator::progress_indicator(containers::page& page, const std::string& alias) :
			d_(*(new impl(page, alias))) {}

		widgets::progress_indicator::~progress_indicator() { delete& d_; }

		widgets::progress_indicator::progress_indicator_specs&
			widgets::progress_indicator::specs() {
			return d_.specs_;
		}

		widgets::progress_indicator::progress_indicator_specs&
			widgets::progress_indicator::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				auto& page = fm.d_.p_pages_.at(page_alias);
				auto results = fm.d_.find_widget(page, path_remaining);
				return results.page.d_page_.get_progress_indicator(results.widget.alias()).specs();
			}

			throw std::invalid_argument("Invalid path");
		}
	}
}
