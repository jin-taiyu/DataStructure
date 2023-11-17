 
#ifndef _BST_H
#define _BST_H

Status InitDSTable(BiTree &DT); 
void DestroyDSTable(BiTree &DT);
BiTree SearchBST(BiTree T,KeyType key);
void SearchBST(BiTree &T,KeyType key,BiTree f,BiTree &p,Status &flag); // Ëã·¨9.5(b)¸Ä 
Status InsertBST(BiTree &T, ElemType e);
void Delete(BiTree &p);
Status DeleteBST(BiTree &T,KeyType key);
void TraverseDSTable(BiTree DT,void(*Visit)(ElemType));

#endif