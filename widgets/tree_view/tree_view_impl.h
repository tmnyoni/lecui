//
// tree_view_impl.h - tree_view_impl interface
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#include <optional>
#include "../widget_impl.h"
#include "../tree_view.h"
#include "../../containers/pane/pane_impl.h"

namespace liblec {
	namespace lecui {
		namespace widgets {
			class tree_view_impl : public widget_impl {
				/// private virtual function overrides
				widgets::specs& generic_specs() override {
					return specs_;
				}

			public:
				/// constructor and destructor
				tree_view_impl(containers::page& page,
					const std::string& alias,
					ID2D1Factory* p_direct2d_factory,
					IDWriteFactory* p_directwrite_factory);
				~tree_view_impl();

				/// virtual function overrides
				widget_type type() override;
				HRESULT create_resources(ID2D1HwndRenderTarget* p_render_target) override;
				void discard_resources() override;
				D2D1_RECT_F& render(ID2D1HwndRenderTarget* p_render_target,
					const D2D1_SIZE_F& change_in_size, const D2D1_POINT_2F& offset,
					const bool& render) override;
				void on_click() override;
				bool hit(const bool& hit) override;

				/// widget specific methods
				widgets::tree_view::tree_view_specs& specs();
				widgets::tree_view::tree_view_specs& operator()();
				void set_tree_pane_specs(containers::pane::pane_specs& specs);

			private:
				// Default constructor and copying an object of this class are not allowed
				tree_view_impl() = delete;
				tree_view_impl(const tree_view_impl&) = delete;
				tree_view_impl& operator=(const tree_view_impl&) = delete;

				/// Private variables
				widgets::tree_view::tree_view_specs specs_, specs_old_;
				ID2D1SolidColorBrush* p_brush_;
				ID2D1SolidColorBrush* p_brush_hot_;
				ID2D1SolidColorBrush* p_brush_disabled_;
				ID2D1SolidColorBrush* p_brush_selected_;
				IDWriteTextFormat* p_text_format_;

				ID2D1Factory* p_direct2d_factory_;
				IDWriteFactory* p_directwrite_factory_;
				IDWriteTextLayout* p_text_layout_;

				const float margin_;

				std::optional<std::reference_wrapper<containers::pane::pane_specs>> tree_pane_specs_;

				/// Private methods.
				void on_selection();
			};
		}
	}
}
