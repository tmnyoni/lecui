/*
** page_impl.h - page_impl interface
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

#include "../../form_common.h"
#include "../h_scrollbar/h_scrollbar.h"
#include "../v_scrollbar/v_scrollbar.h"

#include "../rectangle/rectangle_impl.h"
#include "../label/label_impl.h"
#include "../group/group_impl.h"
#include "../tab_control/tab_control_impl.h"
#include "../../../page.h"
#include "../button/button_impl.h"
#include "../toggle/toggle_impl.h"
#include "../combo/combo_impl.h"
#include "../list/list_impl.h"
#include "../custom/custom_impl.h"
#include "../pane/pane_impl.h"

class liblec::lecui::widgets::page::page_impl {
public:
	page_impl(const std::string& name);
	~page_impl();

	std::string name();
	void directwrite_factory(IDWriteFactory* p_directwrite_factory);
	IDWriteFactory* directwrite_factory();

	void size(const liblec::lecui::size& size);
	const liblec::lecui::size& size();
	void width(const long& width);
	const long width();
	void height(const long& height);
	const long height();

	liblec::lecui::widgets::specs::rectangle&
		add_rectangle(const std::string& name);
	liblec::lecui::widgets::specs::label&
		add_label(const std::string& name);
	liblec::lecui::widgets::specs::group&
		add_group(const std::string& name);
	liblec::lecui::widgets::specs::tab_control&
		add_tab_control(const std::string& name);
	liblec::lecui::widgets::specs::button&
		add_button(const std::string& name);
	liblec::lecui::widgets::specs::toggle&
		add_toggle(const std::string& name);
	liblec::lecui::widgets::specs::combo&
		add_combo(const std::string& name);
	liblec::lecui::widgets::specs::list&
		add_list(const std::string& name);
	liblec::lecui::widgets::specs::custom&
		add_custom(const std::string& name);
	liblec::lecui::widgets::specs::pane&
		add_pane(const std::string& name);

	std::map<std::string,
		liblec::lecui::widgets_implementation::widget&>&
		widgets();
	const std::vector<std::string>&
		widgets_order();
	liblec::lecui::widgets_implementation::h_scrollbar&
		h_scrollbar();
	liblec::lecui::widgets_implementation::v_scrollbar&
		v_scrollbar();
	liblec::lecui::widgets_implementation::group&
		get_group(const std::string& name);
	liblec::lecui::widgets_implementation::tab_control&
		get_tab_control(const std::string& name);
	liblec::lecui::widgets_implementation::toggle&
		get_toggle(const std::string& name);
	liblec::lecui::widgets_implementation::combo&
		get_combo(const std::string& name);
	liblec::lecui::widgets_implementation::list&
		get_list(const std::string& name);
	liblec::lecui::widgets_implementation::custom&
		get_custom(const std::string& name);
	liblec::lecui::widgets_implementation::pane&
		get_pane(const std::string& name);

private:
	IDWriteFactory* p_directwrite_factory_;
	std::string name_;
	liblec::lecui::size size_;

	std::map<std::string, liblec::lecui::widgets_implementation::widget&> widgets_;
	std::vector<std::string> widgets_order_;

	liblec::lecui::widgets_implementation::h_scrollbar h_scrollbar_;
	liblec::lecui::widgets_implementation::v_scrollbar v_scrollbar_;

	std::map<std::string, liblec::lecui::widgets_implementation::rectangle> rectangles_;
	std::map<std::string, liblec::lecui::widgets_implementation::label> labels_;
	std::map<std::string, liblec::lecui::widgets_implementation::group> groups_;
	std::map<std::string, liblec::lecui::widgets_implementation::tab_control> tab_controls_;
	std::map<std::string, liblec::lecui::widgets_implementation::button> buttons_;
	std::map<std::string, liblec::lecui::widgets_implementation::toggle> toggles_;
	std::map<std::string, liblec::lecui::widgets_implementation::combo> combos_;
	std::map<std::string, liblec::lecui::widgets_implementation::list> lists_;
	std::map<std::string, liblec::lecui::widgets_implementation::custom> customs_;
	std::map<std::string, liblec::lecui::widgets_implementation::pane> panes_;
};
