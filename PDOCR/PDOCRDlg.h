// PDOCRDlg.h : header file
//

#pragma once
#include "ImageCtrl.h"
#include <map>


// CPDOCRDlg dialog
class CPDOCRDlg : public CBCGPDialog
{
// Construction
public:
	CPDOCRDlg(CWnd * pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PDOCR_DIALOG };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	DECLARE_MESSAGE_MAP()
public:
	CImageCtrl m_wndPreview;
	CBCGPButton m_btnPaste;
	CBCGPButton m_btnOpen;
	CBCGPButton m_btn11;
	CRichEditCtrl m_wndEdit;
	CBCGPButton m_btnScreenclip;
	CBCGPComboBox m_cmbMode;

	void Run(CString strPath);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPaste();
	afx_msg void OnBnClickedBtnScreenclip();
	afx_msg void OnFeedback();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnShowtask(WPARAM wParam, LPARAM lParam);


	void DisplayOcrRes(const std::string &str);
private:
	NOTIFYICONDATA nid;
	BOOL m_bScreenclip = FALSE;
	std::map<CString, CString> m_mapRecModes;
	std::map<CString, CString> m_mapRecChar;
	CString m_strPath;
public:
	afx_msg void OnBnClickedBtn11();
	afx_msg void OnDrawClipboard();
	afx_msg void OnCbnSelchangeCombo1();
};
