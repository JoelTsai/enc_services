/*******************************************************************
 *
 *    DESCRIPTION:
 *
 *    AUTHOR:
 *
 *    HISTORY:    
 *
 *******************************************************************/

#ifndef __DLL_H
#define __DLL_H

typedef struct __dll_node_t dll_Node_t;
struct __dll_node_t
{
    dll_Node_t* dn_NextPtr;
    dll_Node_t* dn_PrevPtr;
};

#define dll_NodeEntry( NodePtr, Type, ElmtName ) \
    (Type*)((void*)NodePtr - (void*)(&((Type*)0)->ElmtName ))

#define dll_ListEmpty( ListPtr ) \
    (((ListPtr)->dn_NextPtr == (ListPtr)) && \
     ((ListPtr)->dn_PrevPtr == (ListPtr)))

#define dll_InitNode( NodePtr ) \
    ((NodePtr)->dn_PrevPtr = \
     (NodePtr)->dn_NextPtr = (NodePtr))

#define dll_GetListHead( ListPtr ) \
    ((ListPtr)->dn_NextPtr )

#define dll_GetListTail( ListPtr ) \
    ((ListPtr)->dn_PrevPtr )

#ifndef NDEBUG
static __inline void dll_DumpNode( dll_Node_t* NodePtr )
{
/*  assert( NodePtr != (dll_Node_t*)NULL ); */
/*  dbgout( "NodePtr.%p.Prev.%p.Next.%p",
        NodePtr, NodePtr->dn_PrevPtr, NodePtr->dn_NextPtr ); */
}
#endif  /* NDEBUG */

#define dll_ListForEach( pNode, pList ) \
        for ( pNode = (pList)->dn_NextPtr; \
            ( pNode != (pList)); pNode = pNode->dn_NextPtr )

static __inline void dll_ListAddTail( dll_Node_t* ListPtr, dll_Node_t* NodePtr )
{
    dll_Node_t* TailPtr;

/*  assert(( ListPtr != (dll_Node_t*)NULL ) &&
           ( NodePtr != (dll_Node_t*)NULL )); */

    TailPtr = ListPtr->dn_PrevPtr;

    NodePtr->dn_PrevPtr = TailPtr;
    NodePtr->dn_NextPtr = ListPtr;

    TailPtr->dn_NextPtr = NodePtr;
    ListPtr->dn_PrevPtr = NodePtr;
}

static __inline void dll_ListAddHead( dll_Node_t* ListPtr, dll_Node_t* NodePtr )
{
    dll_Node_t* HeadPtr;

/*  assert(( ListPtr != (dll_Node_t*)NULL ) &&
           ( NodePtr != (dll_Node_t*)NULL )); */

    HeadPtr = ListPtr->dn_NextPtr;

    NodePtr->dn_NextPtr = HeadPtr;
    NodePtr->dn_PrevPtr = ListPtr;

    ListPtr->dn_NextPtr = NodePtr;
    HeadPtr->dn_PrevPtr = NodePtr;
}

static __inline void dll_ListDelInit( dll_Node_t* NodePtr )
{
    dll_Node_t* PrevPtr;
    dll_Node_t* NextPtr;

/*  assert( NodePtr != (dll_Node_t*)NULL ); */

    PrevPtr = NodePtr->dn_PrevPtr;
    NextPtr = NodePtr->dn_NextPtr;

    PrevPtr->dn_NextPtr = NextPtr;
    NextPtr->dn_PrevPtr = PrevPtr;

    dll_InitNode( NodePtr );
}

static __inline void dll_MoveList( dll_Node_t* DstPtr, dll_Node_t* SrcPtr )
{
    dll_Node_t* PrevPtr;
    dll_Node_t* NextPtr;

/*  assert(( SrcPtr != (dll_Node_t*)NULL ) &&
           ( DstPtr != (dll_Node_t*)NULL )); */

    if ( !dll_ListEmpty( SrcPtr ))
    {
        PrevPtr = SrcPtr->dn_PrevPtr;
        NextPtr = SrcPtr->dn_NextPtr;

        DstPtr->dn_PrevPtr = PrevPtr;
        DstPtr->dn_NextPtr = NextPtr;

        PrevPtr->dn_NextPtr = DstPtr;
        NextPtr->dn_PrevPtr = DstPtr;

        dll_InitNode( SrcPtr );
    }
}

#endif  /* __DLL_H */
