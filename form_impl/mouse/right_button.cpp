//
// right_button.cpp - right mouse button implementation
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#include "../form_impl.h"

namespace liblec {
	namespace lecui {
		void form::impl::on_rbuttondown(const D2D1_POINT_2F& point) {
			for (auto& [key, child] : _m_children) {
				if (child && IsWindow(child->_d._hWnd) && (child->_d._menu_form || child->_d._tooltip_form)) {
					// close child menu forms and tooltip forms
					child->close();
				}
			}
		}

		void form::impl::on_rbuttonup(const D2D1_POINT_2F& point) {
			bool right_clicked = false;
			std::function<void()> on_right_click_handler = nullptr;

			// check form widgets
			for (auto& widget : _widgets) {
				if (widget.second.is_static() || !widget.second.visible() || !widget.second.enabled())
					continue;

				if (right_clicked)
					break;

				if (!right_clicked &&
					widget.second.contains(point)) {
					right_clicked = true;
					on_right_click_handler = [&]() { widget.second.on_right_click(); };
				}
			}

			class helper {
			public:
				static void check_widgets(containers::page& page,
					const D2D1_POINT_2F& point, bool& clicked,
					std::function<void()>& on_right_click_handler) {
					// check widgets
					for (auto& widget : page._d_page.widgets()) {
						if (widget.second.is_static() || !widget.second.visible() || !widget.second.enabled())
							continue;

						if (!clicked && widget.second.contains(point)) {
							clicked = true;
							on_right_click_handler = [&]() { widget.second.on_right_click(); };
						}

						// failsafe: for good measure
						widget.second.hide_tooltip();

						if (widget.second.type() ==
							widgets::widget_type::tab_pane) {
							// get this tab pane
							auto& tab_pane = page._d_page.get_tab_pane(widget.first);

							auto page_iterator = tab_pane._p_tabs.find(tab_pane._current_tab);

							if (page_iterator != tab_pane._p_tabs.end())
								check_widgets(page_iterator->second, point, clicked,
									on_right_click_handler);
						}
						else
							if (widget.second.type() ==
								widgets::widget_type::pane) {
								// get this pane
								auto& pane = page._d_page.get_pane(widget.first);

								auto page_iterator = pane._p_panes.find(pane._current_pane);

								if (page_iterator != pane._p_panes.end())
									check_widgets(page_iterator->second, point, clicked,
										on_right_click_handler);
							}
					}
				}
			};

			for (auto& it : _p_status_panes)
				helper::check_widgets(it.second, point, right_clicked,
					on_right_click_handler);

			auto page_iterator = _p_pages.find(_current_page);

			if (page_iterator != _p_pages.end())
				helper::check_widgets(page_iterator->second, point, right_clicked,
					on_right_click_handler);

			if (right_clicked) {
				// invoke the on_right_click handler
				if (right_clicked && on_right_click_handler)
					on_right_click_handler();
			}
		}
	}
}
