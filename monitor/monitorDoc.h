// monitorDoc.h : CmonitorDoc ��Ľӿ�
//


#pragma once

class CmonitorDoc : public CDocument
{
protected: // �������л�����
	CmonitorDoc();
	DECLARE_DYNCREATE(CmonitorDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
	virtual void Serialize(CArchive& ar);
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT

// ʵ��
public:
	virtual ~CmonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


