/*
** image_impl.cpp - image widget implementation
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

#include "image_impl.h"
#include "../../containers/page/page_impl.h"

class liblec::lecui::widgets::image::image::image_impl {
public:
	image_impl(liblec::lecui::containers::page& page) :
		page_(page) {}
	liblec::lecui::containers::page& page_;
};

liblec::lecui::widgets::image::image(liblec::lecui::containers::page& page) :
	d_(*(new image_impl(page))) {}

liblec::lecui::widgets::image::~image() { delete& d_; }

liblec::lecui::widgets::specs::image&
liblec::lecui::widgets::image::add(const std::string& name) {
	return d_.page_.d_page_.add_image(name);
}

liblec::lecui::widgets_implementation::image::image(const std::string& page,
	const std::string& name, IWICImagingFactory* p_IWICFactory) :
	p_brush_fill_(nullptr),
	p_brush_border_(nullptr),
	p_brush_hot_(nullptr),
	p_brush_disabled_(nullptr),
	p_brush_selected_(nullptr),
	p_bitmap_(nullptr),
	p_IWICFactory_(p_IWICFactory) {
	page_ = page;
	name_ = name;
	log("constructor: " + page_ + ":" + name_);
}

liblec::lecui::widgets_implementation::image::~image() {
	discard_resources();
	log("destructor: " + page_ + ":" + name_);
}

std::string liblec::lecui::widgets_implementation::image::name() { return name_; }
std::string liblec::lecui::widgets_implementation::image::page() { return page_; }

liblec::lecui::widgets_implementation::widget_type
liblec::lecui::widgets_implementation::image::type() {
	return lecui::widgets_implementation::widget_type::image;
}

HRESULT liblec::lecui::widgets_implementation::image::create_resources(
	ID2D1HwndRenderTarget* p_render_target) {
	log("creating resources:   " + page_ + ":" + name_);
	is_static_ = (specs_.on_click == nullptr);

	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
		hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_fill),
			&p_brush_fill_);
	if (SUCCEEDED(hr))
		hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_border),
			&p_brush_border_);
	if (SUCCEEDED(hr))
		hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_hot),
			&p_brush_hot_);
	if (SUCCEEDED(hr))
		hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_disabled),
			&p_brush_disabled_);
	if (SUCCEEDED(hr))
		hr = p_render_target->CreateSolidColorBrush(convert_color(specs_.color_selected),
			&p_brush_selected_);
	if (SUCCEEDED(hr) && !specs_.file.empty())
		load_bitmap_file(p_render_target, p_IWICFactory_, convert_string(specs_.file).c_str(),
			&p_bitmap_);

	resources_created_ = true;
	return hr;
}

void liblec::lecui::widgets_implementation::image::discard_resources() {
	log("discarding resources: " + page_ + ":" + name_);
	resources_created_ = false;
	safe_release(&p_brush_fill_);
	safe_release(&p_brush_border_);
	safe_release(&p_brush_hot_);
	safe_release(&p_brush_disabled_);
	safe_release(&p_brush_selected_);
	//safe_release(&p_bitmap_);	// to-do: why does this cause an access violation error?
}

D2D1_RECT_F&
liblec::lecui::widgets_implementation::image::render(ID2D1HwndRenderTarget* p_render_target,
	const float& change_in_width, const float& change_in_height, float x_off_set, float y_off_set,
	const bool& render) {
	if (!resources_created_)
		create_resources(p_render_target);

	rect_ = position(specs_.rect, specs_.resize, change_in_width, change_in_height);
	rect_.left -= x_off_set;
	rect_.right -= x_off_set;
	rect_.top -= y_off_set;
	rect_.bottom -= y_off_set;

	if (!render || !visible_)
		return rect_;

	D2D1_ROUNDED_RECT rounded_rect{ rect_,
		specs_.corner_radius_x, specs_.corner_radius_y };

	p_render_target->FillRoundedRectangle(&rounded_rect, is_enabled_ ?
		p_brush_fill_ : p_brush_disabled_);

	if (p_bitmap_) {
		// retrieve the size of the bitmap and define suitably sized rectangle for the image
		const auto size = p_bitmap_->GetSize();
		auto rect_image = D2D1::RectF(0, 0, size.width, size.height);
		fit_rect(rect_, rect_image, false, false, true);

		// draw the bitmap
		p_render_target->DrawBitmap(p_bitmap_, rect_image);
	}

	p_render_target->DrawRoundedRectangle(&rounded_rect, is_enabled_ ?
		p_brush_border_ : p_brush_disabled_, specs_.border);

	if (!is_static_ && is_enabled_) {
		if (hit_ || pressed_)
			p_render_target->DrawRoundedRectangle(&rounded_rect, p_brush_hot_, pressed_ ?
				1.75f : 1.f);

		if (selected_)
			p_render_target->DrawRoundedRectangle(&rounded_rect, p_brush_selected_, pressed_ ?
				1.75f : 1.f);
	}

	return rect_;
}

void liblec::lecui::widgets_implementation::image::on_click() {
	if (specs_.on_click)
		specs_.on_click();
}

liblec::lecui::widgets::specs::image&
liblec::lecui::widgets_implementation::image::specs() { return specs_; }
