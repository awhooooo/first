#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Member {
    private:
        std::vector<std::weak_ptr<Member> > parents;
        std::vector<std::weak_ptr<Member> > spouse;
        std::vector<std::shared_ptr<Member> > children;
        std::string name;

    public:
        Member();
        Member(const std::vector<std::weak_ptr<Member> >& parents, 
               const std::vector<std::weak_ptr<Member> >& spouse,
               const std::vector<std::shared_ptr<Member> >& children,
               const std::string& name);
        ~Member();
        void AddParent(const std::shared_ptr<Member>& parent);
        void AddSpouse(const std::shared_ptr<Member>& spouse);
        void AddChild(const std::shared_ptr<Member>& child);
        std::vector<std::weak_ptr<Member> > getParents();
        std::vector<std::weak_ptr<Member> > getSpouse();
        std::vector<std::shared_ptr<Member> > getChildren();
};

class FamilyTree {
    private:
        std::vector<std::shared_ptr<Member> > entire_family;

    public:
        FamilyTree();
        FamilyTree(const std::vector<std::shared_ptr<Member> >& entire_family);
        ~FamilyTree();
        void AddMember(const std::shared_ptr<Member>& member);
        int calculate_distance(const std::shared_ptr<Member>& mem1, const std::shared_ptr<Member>& mem2);
};
