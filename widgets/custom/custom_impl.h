/*
** custom_impl.h - custom_impl interface
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
#include "../custom.h"

namespace liblec {
	namespace lecui {
		namespace widgets {
			class custom_impl : public widget_impl {
				/// private virtual function overrides
				widgets::specs& generic_specs() override {
					return specs_;
				}

			public:
				/// Prevent the use of the default constructor.
				custom_impl() = delete;

				/// constructor and destructor
				custom_impl(containers::page& page,
					const std::string& alias,
					IDWriteFactory* p_directwrite_factory,
					IWICImagingFactory* p_iwic_factory);
				~custom_impl();

				/// virtual function overrides
				widget_type type() override;
				HRESULT create_resources(ID2D1HwndRenderTarget* p_render_target) override;
				void discard_resources() override;
				D2D1_RECT_F& render(ID2D1HwndRenderTarget* p_render_target,
					const D2D1_SIZE_F& change_in_size, const D2D1_POINT_2F& offset,
					const bool& render) override;

				/// widget specific methods
				widgets::custom::custom_specs& specs();
				widgets::custom::custom_specs& operator()();

			private:
				/// Prevent copying an object of this class.
				custom_impl(const custom_impl&);
				custom_impl& operator=(const custom_impl&);

				/// Private variables
				widgets::custom::custom_specs specs_, specs_old_;

				IDWriteFactory* p_directwrite_factory_;
				IWICImagingFactory* p_iwic_factory_;
			};
		}
	}
}
