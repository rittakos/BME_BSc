#include <iostream>

#include "Component.h"
#include "Composit.h"

int main() {
    auto root = std::make_shared<Composit>("root");
    root->add(std::make_shared<Leaf>("key", "value"));

    auto nested = std::make_shared<Composit>("nested");
    nested->add(std::make_shared<Leaf>("key", "value"));
    
    root->add(nested);

    std::cout << root->toString() << '\n';
}
