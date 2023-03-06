#pragma once
#include "stdafx.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

class CImageCtrl : public CStatic
{
public:
	CImageCtrl();
	~CImageCtrl();
	enum sizeType { SIZE_ORIGINAL, SIZE_SCALETOFIT, SIZE_CUSTOM };
	enum allignmentType { ALLIGN_TOPLEFT, ALLIGN_TOPCENTER, ALLIGN_TOPRIGHT, ALLIGN_MIDDLELEFT, ALLIGN_MIDDLECENTER, ALLIGN_MIDDLERIGHT, ALLIGN_BOTTOMLEFT, ALLIGN_BOTTOMCENTER, ALLIGN_BOTTOMRIGHT };

	void setSizeType(int sizeType) { m_sizeType = sizeType; }                          // Size type: SIZE_ORIGINAL, SIZE_SCALETOFILL, SIZE_CUSTOM.
	double getLeft() { return m_left; }                                                // x-coordinate of the image top-left point.
	double getTop() { return m_top; }                                                  // y-coordinate of the image top-left point.
	void setWidth(double width) { m_width = width; }                                   // Set image width (pixels).
	double getWidth() { return m_width; }                                              // Image width (pixels).
	double getWidthOriginal() { return m_widthOriginal; }                              // Image original width (pixels).
	void setHeight(double height) { m_height = height; }                               // Set image height (pixels).
	double getHeight() { return m_height; }                                            // Image height (pixels).
	double getHeightOriginal() { return m_heightOriginal; }                            // Image original height (pixels).

	void setMaintainAspectRatio(bool maintainAspectRatio) { m_maintainAspectRatio = maintainAspectRatio; }
	double setAspectRatio(double aspectRatio) { return m_aspectRatio = aspectRatio; }
	double getAspectRatio() { return m_aspectRatio; }                                  // Case "no image": CStatic->ClientRectangle (height / width), Case "image": m_height / m_width.
	void setAllignmentType(int allignmentType) { m_allignmentType = allignmentType; }  // Image alignment type inside control: ALLIGN_TOPLEFT, ALLIGN_TOPCENTER,... 
	void setPanMode(bool isPanMode) { m_isPanMode = isPanMode; }                       // Enable/disable PAN mode.
	void setZoomMode(bool isZoomMode) { m_isZoomMode = isZoomMode; }                   // Enable/disable ZOOM mode.

	bool isImageShown() { return m_isImageShown > 0; }                                 // Is image shown in the control?
	void update();                                                                     // Update image in the control.
	void erase();                                                                      // Erase image from the control.

	BOOL load(CString szFilePath);                                                     // Loads an image from file.
	BOOL load(IStream* piStream);                                                      // Loads an image from IStream interface.
	BOOL load(BYTE* pData, size_t nSize);                                              // Loads an image from BYTE array.
	BOOL load(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType, WORD wlan);             // Loads an image from resource.
	BOOL load(HBITMAP bmp);
	BOOL convert(CString pathName, CString imageType);                                 // Converts image to specified image type and saves it to *.imageType file.
	BOOL iconResourceToFile(CString resPathName, LPCTSTR lpName, WORD wlan, CString icoPathName); // Loads icon from resource EXE or DLL and saves it to *.ico file.

private:
	void release(bool calcFrameAspectRatio = true);                                    // Release allocated memory and initialize.

	int m_sizeType;             // Size type: SIZE_ORIGINAL, SIZE_SCALETOFILL, SIZE_CUSTOM.
	double m_left;              // x-coordinate of the image top-left point.
	double m_top;               // y-coordinate of the image top-left point.
	double m_width;             // Image width (pixels).
	double m_height;            // Image height (pixels).
	double m_widthOriginal;     // Image original width (pixels).
	double m_heightOriginal;    // Image original height (pixels).
	bool m_maintainAspectRatio; // Maintain aspect ratio or not.
	double m_aspectRatio;       // Aspect ratio factor:  Case "no image": CStatic->ClientRectangle (height / width), Case "image": m_height / m_width.
	int m_allignmentType;       // Image alignment type inside control: ALLIGN_TOPLEFT, ALLIGN_TOPCENTER,... 
	bool m_isPanMode;           // Enabled/disabled PAN mode.
	bool m_isZoomMode;          // Enabled/disabled ZOOM mode.
	double m_zoomMin;           // Minimal rectangle side value (in pixels) on ZOOM action.
	double m_zoomMax;           // Maximal rectangle side value (in pixels) on ZOOM action.
	BOOL m_isImageShown;        // Is image shown in the control?

	BOOL m_isInitialShow;       // Is initial image show? TRUE: if not derived from PAN/ZOOM mode action, FALSE: otherwise.
	CPoint m_panAtPt;           // Origin point of PAN action.
	CPoint m_panOffset;         // Offset distances at PAN action.
	CPoint m_zoomAtPt;          // Point at zoom event, which is triggered by mouse wheel scrolling ON image.
	double m_zoomFactor;        // Zoom factor: Case > 1: zoom in, Case < 1: zoom out.

	Bitmap* m_pBmp;             // Pointer to GDI+ bitmap.
	ULONG_PTR m_gdiplusToken;   // GDI+ Token.

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()
};
