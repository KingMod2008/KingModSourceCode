#pragma once
#include "SdkHeaders.hpp"

inline bool validUObject(UObject* obj)
{
	return obj && !(obj->ObjectFlags &EObjectFlags::RF_Marked);
}

inline bool sameId(FUniqueNetId& left,FUniqueNetId& right)
{
	return (left.EpicAccountId == right.EpicAccountId) && (left.Uid == right.Uid);
}

typedef float         FLOAT;
typedef uint8_t       BYTE;
typedef int32_t       INT;
typedef uint32_t      UINT;
typedef UINT          UBOOL;
typedef unsigned long BITFIELD;
typedef double        DOUBLE;

template <class ElementType> class TLinkedList
{
public:
	
	class TIterator
	{
	private:

		struct PrivateBooleanHelper
		{
			INT Value;
		};

	public:
		TIterator(TLinkedList* FirstLink) : CurrentLink(FirstLink) {}

		
		void Next()
		{
			checkSlow(CurrentLink);
			CurrentLink = CurrentLink->NextLink;
		}

		TIterator& operator++()
		{
			Next();
			return *this;
		}

		TIterator operator++(int)
		{
			TIterator Tmp(*this);
			Next();
			return Tmp;
		}

		
		typedef bool PrivateBooleanType;
		operator PrivateBooleanType() const { return CurrentLink != NULL ? &PrivateBooleanHelper::Value : NULL; }
		bool operator!() const { return !operator PrivateBooleanType(); }


		ElementType& operator->() const
		{
			checkSlow(CurrentLink);
			return CurrentLink->Element;
		}
		ElementType& operator*() const
		{
			checkSlow(CurrentLink);
			return CurrentLink->Element;
		}

	private:
		TLinkedList* CurrentLink;
	};


	TLinkedList() : NextLink(NULL), PrevLink(NULL) {}
	TLinkedList(const ElementType& InElement) : Element(InElement), NextLink(NULL), PrevLink(NULL) {}

	
	void Unlink()
	{
		if (NextLink)
		{
			NextLink->PrevLink = PrevLink;
		}
		if (PrevLink)
		{
			*PrevLink = NextLink;
		}

		NextLink = NULL;
		PrevLink = NULL;
	}

	
	void Link(TLinkedList*& Before)
	{
		if (Before)
		{
			Before->PrevLink = &NextLink;
		}
		NextLink = Before;
		PrevLink = &Before;
		Before   = this;
	}

	
	bool IsLinked() { return PrevLink != NULL; }


	ElementType&       operator->() { return Element; }
	const ElementType& operator->() const { return Element; }
	ElementType&       operator*() { return Element; }
	const ElementType& operator*() const { return Element; }
	TLinkedList*       Next() { return NextLink; }

private:
	ElementType   Element;
	TLinkedList*  NextLink;
	TLinkedList** PrevLink;
};

struct FMipBiasFade
{
	FLOAT TotalMipCount;
	FLOAT MipCountDelta;
	FLOAT StartTime;
	FLOAT MipCountFadingRate;
	FLOAT BiasOffset;
};

enum EShaderFrequency
{
	SF_Vertex         = 0,
	SF_Hull           = 1,
	SF_Domain         = 2,
	SF_Pixel          = 3,
	SF_Geometry       = 4,
	SF_Compute        = 5,
	SF_NumFrequencies = 6,
};

class FD3D11DynamicRHI;
class ID3D11ShaderResourceView;
class ID3D11RenderTargetView;
class ID3D11DepthStencilView;
class ID3D11Texture2D;

struct FD3D11Texture2D
{
	ID3D11ShaderResourceView* View;
	ID3D11ShaderResourceView* ViewLinear;
	ID3D11RenderTargetView*   RenderTargetView;
	ID3D11DepthStencilView*   DepthStencilView;
	TArray<INT>               BoundShaderResourceSlots[SF_NumFrequencies];
	const UINT                SizeX;
	const UINT                SizeY;
	const UINT                SizeZ;
	const UINT                NumMips;
	EPixelFormat              Format;
	FD3D11DynamicRHI*         D3DRHI;
	INT                       MemorySize;
	ID3D11Texture2D*          Resource;
	const BITFIELD            bCubemap : 1;
	UINT                      Flags;

	FORCEINLINE ID3D11ShaderResourceView* GetShaderResourceView() { return View; }
	virtual void                          DummyForVptr() {}
};

struct FRenderResource
{
	TLinkedList<FRenderResource*>* ResourceLink;
	BITFIELD                       bInitialized : 1;

	virtual ~FRenderResource() {}
};

struct FTexture : public FRenderResource
{
	FD3D11Texture2D* TextureRHI;
	void*            SamplerStateRHI;
	mutable DOUBLE   LastRenderTime;
	FMipBiasFade     MipBiasFade;
	UBOOL            bGreyScaleFormat;

	
	UBOOL bIgnoreGammaConversions;
};

struct FTextureResource : public FTexture
{
	FRenderCommandFence ReleaseFence;
};

