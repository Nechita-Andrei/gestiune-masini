#pragma once
#include "RepoMasina.h"
class UndoAction
{
public:
	UndoAction() {};
	void doUndo(RepositoryCars& repo, std::vector<RepositoryCars>& undoList) {
		if (undoList.size() == 0) {
			throw Exception{ "Can't undo!!\n" };
		}
		repo.clear();
		RepositoryCars new_r = undoList.back();
		undoList.pop_back();
		repo = new_r;
	};
	~UndoAction() {};
};
