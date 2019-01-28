// PlmDef.h : �������ͷ�ļ�,����ϵͳ�õĺ꣬���Ա����еĹ���ʹ��
//

#pragma once

#pragma warning(disable:4786)
#include <list>
#include <map>
#include <unordered_map>

//pointer
#define DELETE_POINTER(p) \
	if(p!=NULL) {delete p; p = NULL;}

//AutoClean
//ָ���ڴ��Զ��ͷ� T* p = new T;
template<class T>
class CPtrAutoClean  
{
public:
	CPtrAutoClean(T*& p):m_p(p){m_b = false;}
	virtual ~CPtrAutoClean()
	{
		if(m_p != NULL && !m_b)
		{
			delete m_p;
			m_p = NULL;
		}
	}

	void Terminate(){m_b = true;}

private:
	T*&   m_p;
	bool m_b;
};

//�����ڴ��Զ��ͷ� T* p = new T[];
template<class T>
class CArrayAutoClean  
{
public:
	CArrayAutoClean(T*& p):m_p(p){m_b = false;}
	virtual ~CArrayAutoClean()
	{
		if(m_p != NULL && !m_b)
		{
			delete[] m_p;
			m_p = NULL;
		}
	}

	void Terminate(){m_b = true;}

private:
	T*&   m_p;
	bool m_b;
};

//��������ָ����Զ��ͷ�
template<class T>
class CRefPtrAutoClean  
{
public:
	CRefPtrAutoClean(T*& p):m_p(p){m_b = false;}
	virtual ~CRefPtrAutoClean()
	{
		if(m_p != NULL && !m_b)
		{
			m_p->Release();
			m_p = NULL;
		}
	}

	void Terminate(){m_b = true;}

private:
	T*&   m_p;
	bool m_b;
};

//�б���Զ��ͷ�std::list<T*>
//ע�⣺ֻ�ͷ��б�����ݣ��������Ϊ�ӿڣ�����б�Ϊnew std::list<T*>���������಻�����ͷ�
template<class T>
class CRefListAutoClean  
{
public:
	CRefListAutoClean(std::list<T*>& lst):m_list(lst){m_b = false;}
	virtual ~CRefListAutoClean()
	{
		if (!m_b)
		{
			std::list<T*>::iterator itr;
			for(itr=m_list.begin();itr!=m_list.end();++itr)
			{
				_ASSERT(*itr != NULL);
				(*itr)->Release();
				*itr = NULL;
			}
			m_list.clear();
		}
	}

	void Terminate(){m_b = true;}

private:
	std::list<T*>&   m_list;
	bool			 m_b;
};


//�б���Զ��ͷ�std::list<T*>
//ע�⣺ֻ�ͷ��б�����ݣ�����б�Ϊnew std::list<T*>���������಻�����ͷ�
template<class T>
class CListAutoClean  
{
public:
	CListAutoClean(std::list<T*>& lst):m_list(lst){m_b = false;}
	virtual ~CListAutoClean()
	{
		if (!m_b)
		{
			std::list<T*>::iterator itr;
			for(itr=m_list.begin();itr!=m_list.end();++itr)
			{
				_ASSERT(*itr != NULL);
				delete (T*)*itr;
				*itr = NULL;
			}
			m_list.clear();
		}
	}

	void Terminate(){m_b = true;}

private:
	std::list<T*>&   m_list;
	bool			 m_b;
};

//�б���Զ��ͷ�std::map<key,T*>
//ע�⣺ֻ�ͷ��б�����ݣ�����б�Ϊnew std::map<T*>���������಻�����ͷ�
template<class TKey, class TValue>
class CMapValueAutoClean 
{
public:
	CMapValueAutoClean(std::map<TKey, TValue*>& map):m_map(map){m_b = false;}
	virtual ~CMapValueAutoClean()
	{
		if (!m_b)
		{
			for(auto itr=m_map.begin();itr!=m_map.end();++itr)
			{
				_ASSERT((itr->second) != NULL);
				delete (TValue*)(itr->second);
				(itr->second) = NULL;
			}
			m_map.clear();
		}
	}

	void Terminate(){m_b = true;}

private:
	std::map<TKey, TValue*>&   m_map;
	bool			 m_b;
};

//�б���Զ��ͷ�std::map<key,T*>
//ע�⣺ֻ�ͷ��б�����ݣ�����б�Ϊnew std::map<T*>���������಻�����ͷ�
template<class TKey, class TValue>
class CUnorderedMapAutoClean
{
public:
	CUnorderedMapAutoClean(std::unordered_map<TKey, TValue*>& _unordered_map):m_unordered_map(_unordered_map){m_b = false;}
	virtual ~CUnorderedMapAutoClean()
	{
		if (!m_b)
		{
			for(auto itr=m_unordered_map.begin(); itr != m_unordered_map.end(); ++itr)
			{
				_ASSERT((itr->second) != NULL);
				delete (TValue*)(itr->second);
				(itr->second) = NULL;
			}
			m_unordered_map.clear();
		}
	}
	void Terminate(){m_b = true;}

private:
	std::unordered_map<TKey, TValue*>&   m_unordered_map;
	bool			 m_b;
};

//�б���Զ��ͷ�CPtrList<T*>
//ע�⣺ֻ�ͷ��б�����ݣ�����б�Ϊnew CPtrList<T*>���������಻�����ͷ�
template<class T>
class CPtrListAutoClean  
{
public:
	CPtrListAutoClean(std::list<T*>& lst):m_list(lst){m_b = false;}
	virtual ~CPtrListAutoClean()
	{
		if (!m_b)
		{
			POSITION pos = m_list.GetHeadPosition();
			while(pos != NULL)
			{
				T* p = (T*)m_list.GetNext(pos);
				delete p;
				p = NULL;
			}
			m_list.RemoveAll();
		}
	}

	void Terminate(){m_b = true;}

private:
	std::list<T*>&   m_list;
	bool		m_b;
};
