//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* toy */
#include <editor/Generated/Forward.h>
#include <uio/Unode.h>

#include <vector>

using namespace mud; namespace toy
{
	using Selection = std::vector<Ref>;

	TOY_EDITOR_EXPORT void context_menu(Widget& parent, Selector& selector, Ref object);

	TOY_EDITOR_EXPORT void edit_toolbox(Widget& parent, Toolbox& toolbox);
	TOY_EDITOR_EXPORT void edit_toolbelt(Widget& parent, Toolbelt& toolbelt);

	TOY_EDITOR_EXPORT void edit_selection(Widget& parent, Selection& selection);
	TOY_EDITOR_EXPORT void edit_selector(Widget& parent, Selector& selector);

	TOY_EDITOR_EXPORT void scene_edit(Widget& parent, World& world);

	TOY_EDITOR_EXPORT void registry(Widget& parent, Indexer& indexer, Selection& selection);
	TOY_EDITOR_EXPORT void registry_section(Widget& parent, Indexer& indexer, Selection& selection);
	TOY_EDITOR_EXPORT void library(Widget& parent, const std::vector<Type*>& types, Selection& selection);
	TOY_EDITOR_EXPORT void library_section(Widget& parent, const std::vector<Type*>& types, Selection& selection);

	TOY_EDITOR_EXPORT void editor_menu(Widget& parent, ActionGroup& action_group);
	TOY_EDITOR_EXPORT void editor_menu_bar(Widget& parent, Editor& editor);
	TOY_EDITOR_EXPORT void editor_graph(Widget& parent, Editor& editor, Selection& selection);

	TOY_EDITOR_EXPORT void editor_components(Widget& parent, Editor& editor);
	TOY_EDITOR_EXPORT void editor(Widget& parent, Editor& editor);
}