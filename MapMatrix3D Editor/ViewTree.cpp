// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ �������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI �����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ���ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

#include "stdafx.h"
#include "ViewTree.h"
//#include "UseEventHandler.h"
#include "FileView.h"
#include "MapMatrix3D Editor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFileView* g_mfcFileView;
//extern CPickHandler* g_mfcPickHander;
/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ��������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//TODO: �ڴ����ӿؼ�֪ͨ�����������
	CPoint point;
	GetCursorPos(&point);					       //��ȡ��Ļ�������   
	ScreenToClient(&point);						   //ת���ɿͻ�����   
	UINT uFlag;									   //�����йص�����Ե���Ϣ������   
	HTREEITEM hTree = HitTest(point, &uFlag);	   //������CtreeTtrl�����Ĺ��ĵ�ǰλ�ú;��   
	
	if((TVHT_NOWHERE & uFlag))   
	{     
		return;   
	}   
	
	if (hTree && (TVHT_ONITEMSTATEICON & uFlag))   //���и�ѡ��   
	{     
		SelectItem(hTree);      
		BOOL bCheck = GetCheck(hTree);   //��ȡ��ǰ��ѡ״̬  
		HTREEITEM hParentTree = GetParentItem(hTree);
		HTREEITEM hChildTree = GetChildItem(hTree);

		if (hParentTree)
		{
			SetCheck(hParentTree, !bCheck);
		}
		
		if (hChildTree)
		{
			SetCheck(hChildTree, !bCheck);
		}

		//�������ػ���ʾ
		int selectCol = g_mfcFileView->getSelectedItemCount();

		if (selectCol < 0)
		{
			return;
		}

		theApp.ShowOrHideSceneGroup(selectCol, !bCheck);
	}   

	 *pResult = 0; 
}