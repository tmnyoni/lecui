/*
** image.cpp - image widget implementation
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

#include "../image.h"
#include "../../form_impl.h"

namespace liblec {
	namespace lecui {
		bool widgets::image_specs::operator==(const image_specs& param) {
			return
				// generic specs
				specs::operator==(param) &&

				// widget specific specs
				(color_border == param.color_border) &&
				(file == param.file) &&
				(png_resource == param.png_resource);
		}

		bool widgets::image_specs::operator!=(const image_specs& param) {
			return !operator==(param);
		}

		class widgets::image::impl {
		public:
			impl(containers::page& page) :
				page_(page) {}
			containers::page& page_;
		};

		widgets::image::image(containers::page& page) :
			d_(*(new impl(page))) {}

		widgets::image::~image() { delete& d_; }

		widgets::image_specs&
			widgets::image::add(const std::string& alias) {
			return d_.page_.d_page_.add_image(alias);
		}

		widgets::image_specs&
			widgets::image::specs(form& fm, const std::string& path) {
			const auto idx = path.find("/");

			if (idx != std::string::npos) {
				const auto page_alias = path.substr(0, idx);
				const auto path_remaining = path.substr(idx + 1);
				auto& page = fm.d_.p_pages_.at(page_alias);
				auto results = fm.d_.find_widget(page, path_remaining);
				return results.page.d_page_.get_image(results.widget.alias()).specs();
			}

			throw std::invalid_argument("Invalid path");
		}
	}
}
