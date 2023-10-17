#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx) {
	// �ʱ�ȭ
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr; // ����üũ �ϱ� ���� HRESULT

	// WIC factory ����
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);

	// decodec ����
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder
	);

	// �̹����� �������� ����
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// ������ ����
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// ������ ����
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	// �����͸� ����ؼ� D2D1Bitamp ����
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);

	if (wicFactory) {
		wicFactory->Release();
	}

	if (wicDecoder) {
		wicDecoder->Release();
	}

	if (wicConverter) {
		wicConverter->Release();
	}

	if (wicFrame) {
		wicFrame->Release();
	}

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
}

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight):SpriteSheet(filename, gfx){
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spriteAccross = (int)bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet() {
	if (bmp) {
		bmp->Release();
	}
}

void SpriteSheet::Draw() {
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)
	);
}

void SpriteSheet::Draw(int index, float x, float y) {
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spriteAccross) * spriteWidth),
		(float)((index / spriteAccross) * spriteHeight),
		(float)((index % spriteAccross) * spriteWidth) + spriteWidth,
		(float)((index / spriteAccross) * spriteHeight) + spriteHeight
	);

	D2D_RECT_F dest = D2D1::RectF(
		x,
		y,
		x + spriteWidth,
		y + spriteHeight
	);

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		src
	);
}

void SpriteSheet::Draw(int index, float positionX, float positionY, float sizeX, float sizeY){
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spriteAccross) * spriteWidth),
		(float)((index / spriteAccross) * spriteHeight),
		(float)((index % spriteAccross) * spriteWidth) + spriteWidth,
		(float)((index / spriteAccross) * spriteHeight) + spriteHeight
	);

	D2D_RECT_F dest = D2D1::RectF(
		positionX,
		positionY,
		positionX + sizeX,
		positionY + sizeY
	);

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		src
	);
}

int SpriteSheet::GetSpriteWidth() {
	return spriteWidth;
}

int SpriteSheet::GetSpriteHeight() {
	return spriteHeight;
}