// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/GCObject.h"
#include "UObject/ObjectPtr.h"

class FBYGRichTextModule : public IModuleInterface, public FGCObject
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Begin FGCObject overrides
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;
	// End FGCObject overrides

	const FSlateBrush* GetIconBrush( const FString& Path, const FVector2D& MaxSize );
	class UBYGRichTextStylesheet* GetFallbackStylesheet() const { return FallbackStylesheet; }

    TSharedPtr<class FSlateStyleSet> SlateStyleSet;

    virtual FString GetReferencerName() const override
    {
        return TEXT("FBYGRichTextModule");
    }

protected:
	TMap<FString, FSlateBrush> InlineIconsCache;
	TArray<UTexture2D*> IconTextures;
	FSlateBrush NullIcon;

	void OnPostEngineInit();

	// Default stylesheet used if no stylesheet is chosen, or there are problems
	TObjectPtr<class UBYGRichTextStylesheet> FallbackStylesheet = nullptr;
};
