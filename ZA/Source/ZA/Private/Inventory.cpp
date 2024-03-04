// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include <algorithm>

Inventory::Inventory()
{
	
}

Inventory::~Inventory()
{

}

bool Inventory::InventoryUnit::compare(InventoryUnit &a, InventoryUnit &b) {
	if (a.itemAmount == 0) return false;
	if (b.itemAmount == 0) return true;

	return a.itemCode < b.itemCode;
}

void Inventory::SortInventory() {
	std::sort(_units, _units + INVENTORY_CAPACITY, InventoryUnit::compare);
}

bool Inventory::TryAddItem(int32 itemCode) {
	// �������� �߰��� ��ġ
	int targetPos = -1;

	for (int i = 0; i < INVENTORY_CAPACITY; i++) {
		// ������ �������� �ְ�, �뷮�� �ʰ����� �ʴ� ������ �����ϴ� ù ��° ��ġ�� �߰�
		if (i == itemCode && _units[i].itemAmount < INVENTORY_UNIT_CAPACITY) {
			targetPos = i;
			break;
		}
		if (targetPos != -1) continue;
		// ��� ������ Ȯ������ �� ������ �������� ���ų� ��� �뷮�� ����á�ٸ� ù ��° ��ĭ�� �߰�
		if (_units[i].itemAmount == 0) targetPos = i;
	}

	// targetPos�� -1�̸� �������� �߰��� ������ �߰����� ���� ��
	if (targetPos == -1)
		return false;

	_units[targetPos].itemCode = itemCode;
	_units[targetPos].itemAmount++;

	return true;

}

bool Inventory::TryAddItemAt(int32 itemCode, uint32 idx) {

	// idx�� �ٸ� �������� �̹� �ִٸ� �߰� �Ұ���
	if (_units[idx].itemAmount != itemCode && _units[idx].itemAmount > 0) {
		return false;
	}

	_units[idx].itemCode = itemCode;
	_units[idx].itemAmount++;

	return true;

}

uint32 Inventory::GetItemAmountAt(uint32 idx) {
	return _units[idx].itemAmount;
}

int32 Inventory::GetItemCodeAt(uint32 idx) {
	if (GetItemAmountAt(idx) == 0)
		return -1;

	return _units[idx].itemCode;
	
}