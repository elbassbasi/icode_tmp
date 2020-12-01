/*
 * IViewPart.h
 *
 *  Created on: 15 mai 2020
 *      Author: Azeddine El Bassbasi
 */

#ifndef ICODE_INCLUDE_UI_IVIEWPART_H_
#define ICODE_INCLUDE_UI_IVIEWPART_H_
#include "IWorkbenchPart.h"

class IViewPart: public IWorkbenchPart {
public:
};

class ICODE_PUBLIC ViewPart : public IViewPart {
public:
	int IncRef();
	int DecRef();
	WControl* GetPartControl(WComposite *parent);
	void Dispose();
	const char* GetTitle();
	int GetTitleImage();
	const char* GetTitleToolTip();
	void SetFocus();
protected:
	int ref;
};

#endif /* ICODE_INCLUDE_UI_IVIEWPART_H_ */
