// acqDoc.h : CacqDoc ��Ľӿ�
//


#pragma once

class CacqDoc : public CDocument
{
protected: // �������л�����
	CacqDoc();
	DECLARE_DYNCREATE(CacqDoc)

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
	virtual ~CacqDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


