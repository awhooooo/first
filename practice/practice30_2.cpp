#include "practice30.hpp"

int main() {

    auto parent1_1 = std::make_shared<Member>();
    auto parent1_2 = std::make_shared<Member>();
    auto child1_1 = std::make_shared<Member>();
    auto child1_2 = std::make_shared<Member>();

    auto parent2_1 = std::make_shared<Member>();
    auto parent2_2 = std::make_shared<Member>();
    auto child2_1 = std::make_shared<Member>();
    auto child2_2 = std::make_shared<Member>();

    auto grandparent1_1 = std::make_shared<Member>();
    auto grandparent1_2 = std::make_shared<Member>();

    child1_1->AddParent(parent1_1); child1_1->AddParent(parent1_2);
    parent1_1->AddChild(child1_1); parent1_2->AddChild(child1_1);
    child1_2->AddParent(parent1_1); child1_2->AddParent(parent1_2);
    parent1_1->AddChild(child1_2); parent1_2->AddChild(child1_2);
    parent1_1->AddSpouse(parent1_2); parent1_2->AddSpouse(parent1_1);

    child2_1->AddParent(parent2_1); child2_1->AddParent(parent2_2);
    parent2_1->AddChild(child2_1); parent2_2->AddChild(child2_1);
    child2_2->AddParent(parent2_1); child2_2->AddParent(parent2_2);
    parent2_1->AddChild(child2_2); parent2_2->AddChild(child2_2);
    parent2_1->AddSpouse(parent2_2); parent2_2->AddSpouse(parent2_1);

    parent1_1->AddParent(grandparent1_1); parent1_1->AddParent(grandparent1_2);
    grandparent1_1->AddChild(parent1_1); grandparent1_2->AddChild(parent1_1);
    grandparent1_1->AddSpouse(grandparent1_2); grandparent1_2->AddSpouse(grandparent1_1);

    parent2_1->AddParent(grandparent1_1); parent2_1->AddParent(grandparent1_2);
    grandparent1_1->AddChild(parent2_1); grandparent1_2->AddChild(parent2_1);
    grandparent1_1->AddSpouse(grandparent1_2); grandparent1_2->AddSpouse(grandparent1_1);

    //                              grandparent1_1 --- grandparent1_2
    //                                   /                       \
    //                                  /                         \
    //                parent1_2 --- parent1_1                  parent2_1 --- parent2_2
    //                         /   \                                    /    \
    //                        /     \                                  /      \
    //                       /       \                                /        \
    //                 child1_1     child1_2                     child2_1     child2_2  


    FamilyTree family;
    family.AddMember(parent1_1);
    family.AddMember(parent1_2);
    family.AddMember(child1_1);
    family.AddMember(child1_2);
    family.AddMember(parent2_1);
    family.AddMember(parent2_2);
    family.AddMember(child2_1);
    family.AddMember(child2_2);
    family.AddMember(grandparent1_1);
    family.AddMember(grandparent1_2);
    int cold = family.calculate_distance(child1_1, child2_1);
    std::cout << "distance => " << cold << std::endl;
    
    return 0;
}
