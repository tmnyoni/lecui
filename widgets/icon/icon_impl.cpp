/*
** icon_impl.cpp - icon_impl implementation
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

#include "icon_impl.h"

namespace liblec {
	namespace lecui {
		widgets::icon_impl::icon_impl(containers::page& page,
			const std::string& alias) :
			widget_impl(page, alias),
			p_brush_fill_(nullptr),
			p_brush_hot_(nullptr),
			p_brush_disabled_(nullptr),
			p_brush_selected_(nullptr) {}

		widgets::icon_impl::~icon_impl() { discard_resources(); }

		widgets::widget_type
			widgets::icon_impl::type() {
			return lecui::widgets::widget_type::icon;
		}

		HRESULT widgets::icon_impl::create_resources(
			ID2D1HwndRenderTarget* p_render_target) {
			specs_old_ = specs_;
			is_static_ = (specs_.events().click == nullptr);
			h_cursor_ = get_cursor(specs_.cursor);

			HRESULT hr = S_OK;

			if (SUCCEEDED(hr))
				hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_fill),
					&p_brush_fill_);
			if (SUCCEEDED(hr))
				hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_hot),
					&p_brush_hot_);
			if (SUCCEEDED(hr))
				hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_disabled),
					&p_brush_disabled_);
			if (SUCCEEDED(hr))
				hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_selected),
					&p_brush_selected_);

			resources_created_ = true;
			return hr;
		}

		void widgets::icon_impl::discard_resources() {
			resources_created_ = false;
			safe_release(&p_brush_fill_);
			safe_release(&p_brush_hot_);
			safe_release(&p_brush_disabled_);
			safe_release(&p_brush_selected_);
		}

		D2D1_RECT_F&
			widgets::icon_impl::render(ID2D1HwndRenderTarget* p_render_target,
				const D2D1_SIZE_F& change_in_size, const D2D1_POINT_2F& offset, const bool& render) {
			if (specs_old_ != specs_) {
				log("specs changed: " + alias_);
				specs_old_ = specs_;
				discard_resources();
			}

			if (!resources_created_)
				create_resources(p_render_target);

			rect_ = position(specs_.rect, specs_.on_resize, change_in_size.width, change_in_size.height);
			rect_.left -= offset.x;
			rect_.right -= offset.x;
			rect_.top -= offset.y;
			rect_.bottom -= offset.y;

			if (!render || !visible_)
				return rect_;

			return rect_;
		}

		void widgets::icon_impl::on_click() {
			if (specs_.events().click)
				specs_.events().click();
		}

		widgets::icon::icon_specs&
			widgets::icon_impl::specs() { return specs_; }

		widgets::icon::icon_specs&
			widgets::icon_impl::operator()() { return specs(); }
	}
}
