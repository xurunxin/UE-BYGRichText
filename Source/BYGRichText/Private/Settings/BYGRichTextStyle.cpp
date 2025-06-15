// Copyright Brace Yourself Games. All Rights Reserved.

#include "Settings/BYGRichTextStyle.h"
#include <Internationalization/Regex.h>

#define LOCTEXT_NAMESPACE "BYGRichTextModule"

void UBYGRichTextStyle::PostInitProperties()
{
	Super::PostInitProperties();
	SortProperties();
}

void UBYGRichTextStyle::PostLoad()
{
	Super::PostLoad();
	for ( int32 i = Properties.Num() - 1; i >= 0; --i )
	{
		if ( Properties[ i ] == nullptr )
			Properties.RemoveAt( i );
	}
	SortProperties();
}

void UBYGRichTextStyle::AddProperty( UBYGRichTextPropertyBase* Property )
{
	Properties.Add( Property );
}

void UBYGRichTextStyle::SortProperties()
{
	// For now there seems to be a problem with sorting stuff
#if WITH_EDITOR
	TArray<UBYGRichTextPropertyBase*> NewProperties = Properties;
    NewProperties.StableSort([](const UBYGRichTextPropertyBase& A, const UBYGRichTextPropertyBase& B)
    {
        if (!&A || !&B) return false; // 空指针保护
        const int32 OrderA = A.GetClass()->GetIntMetaData("DisplayOrder");
        const int32 OrderB = B.GetClass()->GetIntMetaData("DisplayOrder");
        if (OrderA == OrderB)
        {
            // 次级排序：按类名
            FString NameA = A.GetClass()->GetName();
            FString NameB = B.GetClass()->GetName();
            return NameA < NameB;
        }
        return OrderA < OrderB;
    });

    bool bSomethingChanged = false;
    for (int32 i = 0; i < NewProperties.Num(); ++i)
    {
        if (NewProperties[i] != Properties[i])
        {
            bSomethingChanged = true;
            break;
        }
    }
    if (bSomethingChanged)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sorting reordered something"));
        Properties = NewProperties; // 应用排序结果
    }
#endif
}

bool UBYGRichTextStyle::IsValidID( const FName& InID )
{
	static const FRegexPattern ValidIDPattern( "^[A-Za-z0-9_-]+$" );
	FRegexMatcher Matcher( ValidIDPattern, InID.ToString() );
	return Matcher.FindNext();
}

bool UBYGRichTextStyle::IsValidShortcut( const FString& InShortcut )
{
	// Can't be start/end characters from the stylesheet
	static const FRegexPattern ValidIDPattern( "^[^\\[\\]]+$" );
	FRegexMatcher Matcher( ValidIDPattern, InShortcut.TrimStartAndEnd() );
	return Matcher.FindNext();
}

FString UBYGRichTextStyle::ValidateShortcut( const FString& InShortcut )
{
	// trim any whitespace from the start and end
	return InShortcut.TrimStartAndEnd();
}

#undef LOCTEXT_NAMESPACE
