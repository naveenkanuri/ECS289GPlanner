// Fill out your copyright notice in the Description page of Project Settings.

#include "HTNPluginEditor.h"

#include "Modules/ModuleManager.h"

#include "WorldStateDebugDetails.h"
#include "PropertyEditorModule.h"
#include "LevelEditor.h"
#include "WorldStateDebugTool.h"

DEFINE_LOG_CATEGORY(HTNPluginEditor);

#define LOCTEXT_NAMESPACE "FSHTNPlannerEditor"

void FSHTNPlannerEditor::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("WorldStateDebugTool", FOnGetDetailCustomizationInstance::CreateStatic(&FWorldStateDebugDetails::MakeInstance));

	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

		struct Local
		{
			static void AddWorldStateDebug(FMenuBuilder& MenuBuilder)
			{
				MenuBuilder.AddMenuEntry(
					FText::FromString("HTN WorldState Debug"),
					FText::FromString("Debug Window for the HTN Worldstate"),
					FSlateIcon(),
					FUIAction(FExecuteAction::CreateStatic(&FSHTNPlannerEditor::TriggerWorldStateDebug))
				);
			}
		};

		TSharedRef<FExtender> MenuExtender(new FExtender());
		MenuExtender->AddMenuExtension(
			"Debug",
			EExtensionHook::After,
			NULL,
			FMenuExtensionDelegate::CreateStatic(&Local::AddWorldStateDebug));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	};
}

void FSHTNPlannerEditor::ShutdownModule()
{
	// Unregister the details customization
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

void FSHTNPlannerEditor::TriggerWorldStateDebug()
{
	UWorldStateDebugTool* ToolInstance = NewObject<UWorldStateDebugTool>();
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	
	TSharedRef<SWindow> Window = PropertyModule.CreateFloatingDetailsView(ObjectsToView, false);
	Window->SetTitle(FText::FromString("HTN WorldState Debug"));

	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(&FSHTNPlannerEditor::OnToolWindowClosed, ToolInstance));
}

void FSHTNPlannerEditor::OnToolWindowClosed(const TSharedRef<SWindow>& Window, UWorldStateDebugTool* Instance)
{
	Instance->RemoveFromRoot();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSHTNPlannerEditor, HTNPluginEditor);