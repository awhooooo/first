#include "practice30.hpp"
#include <cassert>
#include <queue>

Member::Member() {
    this->parents = {};
    this->spouse = {};
    this->children = {};
    this->name = "";
}

Member::~Member() {

}

Member::Member(const std::vector<std::weak_ptr<Member> >& parents,
               const std::vector<std::weak_ptr<Member> >& spouse,
               const std::vector<std::shared_ptr<Member> >& children,
               const std::string& name) {
                   this->parents = parents;
                   this->spouse = spouse;
                   this->children = children;
                   this->name = name;
               }

void Member::AddParent(const std::shared_ptr<Member>& parent) {
    this->parents.emplace_back(parent);
}

void Member::AddSpouse(const std::shared_ptr<Member>& spouse) {
    this->spouse.emplace_back(spouse);
}

void Member::AddChild(const std::shared_ptr<Member>& child) {
    this->children.emplace_back(child);
}

std::vector<std::weak_ptr<Member> > Member::getParents() {
    return this->parents;
}

std::vector<std::weak_ptr<Member> > Member::getSpouse() {
    return this->spouse;
}

std::vector<std::shared_ptr<Member> > Member::getChildren() {
    return this->children;
}

FamilyTree::FamilyTree() {
    this->entire_family = {};
}

FamilyTree::FamilyTree(const std::vector<std::shared_ptr<Member> >& entire_family) {
    this->entire_family = entire_family;
}

FamilyTree::~FamilyTree() {

}

void FamilyTree::AddMember(const std::shared_ptr<Member>& member) {
    this->entire_family.emplace_back(member);
}

int FamilyTree::calculate_distance(const std::shared_ptr<Member>& mem1, const std::shared_ptr<Member>& mem2) {
    if (mem1 == mem2) {
        return 0;
    }
    else {
        std::unordered_map<std::shared_ptr<Member>, int> distance;
        std::queue<std::shared_ptr<Member> > to_visit;

        distance[mem1] = 0;
        to_visit.push(mem1);

        while (!to_visit.empty()) {
            auto current = to_visit.front();
            to_visit.pop();
            int current_distance = distance[current];

            for (const std::weak_ptr<Member>& parent : current->getParents()) {
                if (auto parent_shr = parent.lock())
                    if (distance.find(parent_shr) == distance.end()) {
                    distance[parent_shr] = current_distance + 1;
                    if (parent_shr == mem2) {
                        return distance[parent_shr];
                    }
                    to_visit.push(parent_shr);
                }
            }

            for (const std::weak_ptr<Member>& spouse : current->getSpouse()) {
                if (auto spouse_shr = spouse.lock())
                    if (distance.find(spouse_shr) == distance.end()) {
                    distance[spouse_shr] = current_distance + 1;
                    if (spouse_shr == mem2) {
                        return distance[spouse_shr];
                    }
                    to_visit.push(spouse_shr);
                }
            }

            for (const std::shared_ptr<Member>& child : current->getChildren()) {
                if (distance.find(child) == distance.end()) {
                    distance[child] = current_distance + 1;
                    if (child == mem2) {
                        return distance[child];
                    }
                    to_visit.push(child);
                }
            }
        }
        return -1;
    }
}
