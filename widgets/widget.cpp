//
// widget.cpp - widget implementation
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#include "widget.h"
#include "../form_impl/form_impl.h"
#include "../timer.h"

namespace liblec {
	namespace lecui {
		namespace widgets {
			bool specs::resize_params::operator==(const resize_params& param) {
				return
					(perc_x == param.perc_x) &&
					(perc_y == param.perc_y) &&
					(perc_width == param.perc_width) &&
					(perc_height == param.perc_height) &&
					(min_x == param.min_x) &&
					(min_y == param.min_y) &&
					(max_x == param.max_x) &&
					(max_y == param.max_y) &&
					(min_width == param.min_width) &&
					(min_height == param.min_height) &&
					(max_width == param.max_width) &&
					(max_height == param.max_height);
			}

			bool specs::resize_params::operator!=(const resize_params& param) {
				return !operator==(param);
			}

			/// This operator is for determining whether to recreate widget resources. It doesn't
			/// represent equality in the sense of widgets having the same characteristics!
			bool specs::operator==(const specs& param) {
				return
					/// Colors
					(color_text_ == param.color_text_) &&
					(color_fill_ == param.color_fill_) &&
					(color_hot_ == param.color_hot_) &&
					(color_selected_ == param.color_selected_) &&
					(color_disabled_ == param.color_disabled_) &&

					/// Font
					(font_ == param.font_) &&
					(font_size_ == param.font_size_) &&

					/// Cursor
					(cursor_ == param.cursor_);
			}

			bool specs::operator!=(const specs& param) {
				return !operator==(param);
			}
		}

		class widget_manager::impl {
		public:
			impl(form& fm) :
				fm_(fm) {}
			form& fm_;
		};

		widget_manager::widget_manager(form& fm) :
			d_(*new impl(fm)) {}
		widget_manager::~widget_manager() {
			delete& d_;
		}

		void widget_manager::enable(const std::string& path, bool enable) {
			d_.fm_.d_.enable(path, enable);
		}

		void widget_manager::show(const std::string& path, bool show) {
			d_.fm_.d_.show(path, show);
		}
		void widget_manager::close(const std::string& path) {
			// use timer in case a widget is closed from its own handler.
			// this way the actual closing will be done (hopefully) outside the handler coz of async.
			// the caller still has to exercise caution by avoiding such logical errors.
			d_.fm_.d_.scheduled_for_closure_.push_back(path);
			timer_management(d_.fm_).add("close_widget_timer", 0,
				[&]() {
					timer_management(d_.fm_).stop("close_widget_timer");
					for (const auto& it : d_.fm_.d_.scheduled_for_closure_)
						d_.fm_.d_.close(it);

					d_.fm_.d_.scheduled_for_closure_.clear();
				});
		}

		void widget_manager::select(const std::string& path) {
			d_.fm_.d_.select(path);
		}
	}
}
