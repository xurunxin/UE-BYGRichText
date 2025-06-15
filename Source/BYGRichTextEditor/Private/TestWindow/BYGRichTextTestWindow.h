// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widget/BYGRichTextBlock.h"
#include "Settings/BYGRichTextStylesheet.h"
#include <UObject/GCObject.h>

#include "UObject/ObjectPtr.h"

class SBYGRichTextTestWindow
	: public SCompoundWidget
	, public FGCObject
{

public:
	SLATE_BEGIN_ARGS( SBYGRichTextTestWindow )
		//: _Messages()
		{}

		/** All messages captured before this log window has been created */
		//SLATE_ARGUMENT( TArray< TSharedPtr<FOutputLogMessage> >, Messages )

	SLATE_END_ARGS()

	virtual ~SBYGRichTextTestWindow();

	/**
	 * Construct this widget.  Called by the SNew() Slate macro.
	 *
	 * @param	InArgs	Declaration used by the SNew() macro to construct this widget
	 */
	void Construct( const FArguments& InArgs );


	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

    virtual FString GetReferencerName() const override
    {
        return TEXT("SBYGRichTextTestWindow");
    }

	// SWidget interface
	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

protected:
	TObjectPtr<class UBYGRichTextBlock> RichTextBlock = nullptr;
	TObjectPtr<class UBYGRichTextStylesheet> Stylesheet = nullptr;

};
