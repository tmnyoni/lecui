/*
** rectangle_impl.h - rectangle_impl interface
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

#pragma once

#include "../widget_impl.h"
#include "../rectangle.h"

namespace liblec {
	namespace lecui {
		namespace widgets_impl {
			class rectangle : public widget {
			public:
				/// <summary>
				/// Get the alias of the special rectangle used with pages. This rectangle is
				/// important as it keeps track of the page dimensions, and makes the scroll
				/// bars work.
				/// </summary>
				/// <returns>The special alias. No other widget should have this alias.</returns>
				static std::string page_rect_alias();

				/// constructor and destructor
				rectangle(const std::string& page_alias,
					const std::string& alias);
				~rectangle();

				/// virtual function overrides
				widgets_impl::widget_type type() override;
				HRESULT create_resources(ID2D1HwndRenderTarget* p_render_target) override;
				void discard_resources() override;
				D2D1_RECT_F& render(ID2D1HwndRenderTarget* p_render_target,
					const D2D1_SIZE_F& change_in_size, const D2D1_POINT_2F& offset,
					const bool& render) override;
				void on_click() override;
				bool contains(const D2D1_POINT_2F& point) override;

				/// widget specific methods
				widgets::rectangle::rectangle_specs& specs();

			private:
				/// Prevent the use of the default constructor.
				rectangle() :
					rectangle(std::string(), std::string()) {}

				/// Prevent copying an object of this class.
				rectangle(const rectangle&);
				rectangle& operator=(const rectangle&);

				/// Private variables
				widgets::rectangle::rectangle_specs specs_, specs_old_;
				ID2D1SolidColorBrush* p_brush_fill_;
				ID2D1SolidColorBrush* p_brush_border_;
				ID2D1SolidColorBrush* p_brush_hot_;
				ID2D1SolidColorBrush* p_brush_disabled_;
				ID2D1SolidColorBrush* p_brush_selected_;
				D2D1_POINT_2F offset_, offset_og_;
				bool og_offset_captured_;
			};
		}
	}
}
