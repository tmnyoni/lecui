//
// close_button_impl.h - close button widget interface
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#include "../../widget_impl.h"

namespace liblec {
	namespace lecui {
		namespace widgets {
			class close_button_specs : public specs {};

			class close_button_impl : public widget_impl {
				/// private virtual function overrides
				widgets::specs& generic_specs() override {
					return specs_;
				}

			public:
				close_button_impl(containers::page& page);
				~close_button_impl();

				/// virtual function overrides
				widget_type type() override;
				HRESULT create_resources(ID2D1HwndRenderTarget* p_render_target) override;
				void discard_resources() override;
				D2D1_RECT_F& render(ID2D1HwndRenderTarget* p_render_target,
					const D2D1_SIZE_F& change_in_size, const D2D1_POINT_2F& offset,
					const bool& render) override;

				/// widget specific methods
				widgets::close_button_specs& specs();
				widgets::close_button_specs& operator()();

			private:
				// Default constructor and copying an object of this class are not allowed
				close_button_impl() = delete;
				close_button_impl(const close_button_impl&) = delete;
				close_button_impl& operator=(const close_button_impl&) = delete;

				widgets::close_button_specs specs_;
				ID2D1SolidColorBrush* p_brush_;
				ID2D1SolidColorBrush* p_brush_hot_;
				ID2D1SolidColorBrush* p_brush_disabled_;
			};
		}
	}
}
