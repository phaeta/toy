//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tool/Tool.h>
#include <tool/ActionStack.h>
#include <tool/EditContext.h>
#include <edit/Forward.h>
#include <edit/Editor/Toolbox.h>

#include <uio/Edit/Script.h>

using namespace mud; namespace toy
{
	using Selection = std::vector<Ref>;

	export_ class refl_ TOY_EDIT_EXPORT PlayTool : public Tool
	{
	public:
		PlayTool(ToolContext& context, Editor& editor);

		virtual void activate() final;

		Editor& m_editor;
	};

	struct refl_ TOY_EDIT_EXPORT ActionGroup
	{
		string m_name;
		std::map<string, std::function<void()>> m_actions;
	};

	class refl_ TOY_EDIT_EXPORT Editor : public EditContext
    {
    public:
		Editor(VisuSystem& visu_system);
        
		Toolbelt m_toolbelt;

		std::map<string, ActionGroup> m_action_groups;

		World* m_edited_world = nullptr;
		bool m_run_game = false;

		void create_scripted_brush();

		ActionGroup& action_group(const string& name);
    };
}