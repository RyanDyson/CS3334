#include <iostream>
#include <unordered_map>
using namespace std;

class FamilyMember {
public:
    int data;
    FamilyMember* parent;

    FamilyMember(int data) {
        this->data = data;
        parent = NULL;
    }

    FamilyMember* getCommonAncestor(FamilyMember* otherMember) {
        unordered_map<FamilyMember*, bool> ancestors;

        FamilyMember* current = this;
        while (current != NULL) {
            ancestors[current] = true;
            current = current->parent;
        }

        current = otherMember;
        while (current != NULL) {
            if (ancestors.find(current) != ancestors.end()) {
                return current;
            }
            current = current->parent;
        }

        return NULL;
    }
};

int main() {
    int n;
    cin >> n;
    while (n--) {
        int rootAncestorNum;
        cin >> rootAncestorNum;
        int k;
        cin >> k;
        k--;

        unordered_map<int, FamilyMember*> allMembers;
        FamilyMember* rootAncestor = new FamilyMember(rootAncestorNum);
        allMembers[rootAncestorNum] = rootAncestor;

        for (int i = 0; i < k; i++) {
            int memberNum, parentNum;
            cin >> memberNum >> parentNum;

            FamilyMember* member = new FamilyMember(memberNum);
            member->parent = allMembers[parentNum];
            allMembers[memberNum] = member;
        }

        int member1Num, member2Num;
        cin >> member1Num >> member2Num;
        FamilyMember* member1 = allMembers[member1Num];
        FamilyMember* member2 = allMembers[member2Num];

        FamilyMember* commonAncestor = member1->getCommonAncestor(member2);
        if (commonAncestor != NULL) {
            cout << commonAncestor->data << endl;
        } else {
            cout << rootAncestor->data << endl;
        }
    }

    return 0;
}