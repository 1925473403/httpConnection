#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Operand {
    int val;
    Operand(int v):val(v) { }
    int get() const { return val; }
};

struct Operator {
    virtual ~Operator() { }
    virtual bool evaluate(Operand*, Operand*) = 0;
    virtual const char* toString() const = 0;
};

struct equals : public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() == b->get();
    }
    const char* toString() const { return "=="; }
};

struct notequals : public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() != b->get();
    }
    const char* toString() const { return "!="; }
};

struct greaterthan : public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() > b->get();
    }
    const char* toString() const { return ">"; }
};

struct lessthan :public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() < b->get();
    }
    const char* toString() const { return "<"; }
};

struct greaterthanequals : public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() >= b->get();
    }
    const char* toString() const { return ">="; }
};

struct lessthanequals : public Operator {
    bool evaluate(Operand *a, Operand *b) {
        return a->get() <= b->get();
    }
    const char* toString() const { return "<="; }
};

static equals DEFAULTEQUALS;
static notequals DEFAULTNOTEQUALS;
static greaterthanequals DEFAULTGREATERTHANEQUALS;
static lessthanequals DEFAULTLESSTHANEQUALS;
static lessthan DEFAULTLESSTHAN;
static greaterthan DEFAULTGREATERTHAN;

struct ExpressionNode {
    Operand *oper[2];
    Operator *op;
    std::string value;
    ExpressionNode():op(nullptr) { oper[0] = nullptr; oper[1] = nullptr; value=""; }
    ExpressionNode(const char *str):op(nullptr) { oper[0] = nullptr; oper[1] = nullptr; value.assign(str); }
    ExpressionNode(Operand *a, Operand *b, Operator *c):op(c) {
        value = "";
        oper[0] = a; oper[1] = b;
    }
    ~ExpressionNode() {
        if (oper[0] != nullptr) delete oper[0];
        if (oper[1] != nullptr) delete oper[1];
        if ((op != nullptr) && ((op != &DEFAULTEQUALS)&&
            (op != &DEFAULTNOTEQUALS) &&
            (op != &DEFAULTLESSTHANEQUALS) &&
            (op != &DEFAULTGREATERTHANEQUALS) &&
            (op != &DEFAULTLESSTHAN) &&
            (op != &DEFAULTGREATERTHAN))) delete op;
        oper[0] = nullptr; oper[1] = nullptr; op = nullptr;
    }
    bool evaluate() {
        return op->evaluate(oper[0], oper[1]);
    }
    std::string toString() {
        stringstream ss;
        if ((oper[0] != nullptr) && (oper[1] != nullptr) && (op != nullptr))
            ss << oper[0]->get() << " " << op->toString() << " " << oper[1]->get();
        else ss << value;
        return ss.str();
    }
};


struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    ExpressionNode *val;
    void indent(int ind) {
        for (int i = 0; i < ind; i++) std::cout << " " ;
    }
    public:
    TreeNode() : left(nullptr), right(nullptr), parent(nullptr), val(nullptr) { }
    TreeNode(ExpressionNode *e) : TreeNode() { val = e; }
    void preOrder(int ind=0) {
        if (left == nullptr && right == nullptr) {
            if (parent!=nullptr && (val != nullptr)) std::cout << ": " << val->toString() << std::endl;
            return;
        } else {
            std::cout << std::endl;
        }
        indent(ind);
        if (val != nullptr) std::cout << val->toString() ;
        if (left != nullptr) {
            left->preOrder(ind + 2);
        }
        if (right != nullptr) {
            indent(ind);
            if (right->parent != nullptr) std::cout << right->parent->toString() ;
            right->preOrder(ind + 2);
        }
    }
    std::string toString() {
        if (val != nullptr) return val->toString() ;
    }
    ~TreeNode() {
        if (left != nullptr) {
            if ((left->parent != nullptr) && (left->parent == this)) left->parent = nullptr;
            delete left;
        }
        if (right != nullptr) {
            if ((right->parent != nullptr) && (right->parent == this)) right->parent = nullptr;
            delete right;
        }
        if (parent != nullptr) delete parent;    
        if (val != nullptr) delete val;
    }
};

int main () {
    int height = 10, age = 20, eyeColor = 4, weight = 150;
    TreeNode root;
    root.val = new ExpressionNode(new Operand(age), new Operand(30), &DEFAULTLESSTHAN);
    root.left = new TreeNode();
    root.left->parent = &root;
    root.left->val = new ExpressionNode(new Operand(eyeColor), new Operand(4), &DEFAULTEQUALS);
    root.left->left = new TreeNode();
    root.left->left->parent = root.left;
    root.left->left->val = new ExpressionNode("YES");
    root.left->right = new TreeNode();
    root.left->right->parent = new TreeNode(new ExpressionNode(new Operand(eyeColor), new Operand(4), &DEFAULTNOTEQUALS));
    root.left->right->val = new ExpressionNode(new Operand(height), new Operand(100), &DEFAULTLESSTHAN);
    root.left->right->left = new TreeNode();
    root.left->right->left->parent = root.left->right;
    root.left->right->left->val = new ExpressionNode("YES");
    root.left->right->right = new TreeNode();
    root.left->right->right->parent = new TreeNode(new ExpressionNode(new Operand(height), new Operand(100), &DEFAULTGREATERTHANEQUALS));
    root.left->right->right->val = new ExpressionNode("NO");

    root.right = new TreeNode();
    root.right->parent = new TreeNode(new ExpressionNode(new Operand(age), new Operand(30), &DEFAULTGREATERTHANEQUALS));
    root.right->val = new ExpressionNode(new Operand(height), new Operand(160), &DEFAULTGREATERTHAN);
    root.right->left = new TreeNode();
    root.right->left->parent = root.right;
    root.right->left->val = new ExpressionNode("NO");
    root.right->right = new TreeNode();
    root.right->right->parent = new TreeNode(new ExpressionNode(new Operand(height), new Operand(160), &DEFAULTLESSTHANEQUALS));
    root.right->right->val = new ExpressionNode(new Operand(eyeColor), new Operand(3), &DEFAULTEQUALS);
    root.right->right->left = new TreeNode();
    root.right->right->left->parent = root.right->right;
    root.right->right->left->val = new ExpressionNode("YES");
    root.right->right->right = new TreeNode();
    root.right->right->right->parent = new TreeNode(new ExpressionNode(new Operand(eyeColor), new Operand(3), &DEFAULTNOTEQUALS));
    root.right->right->right->val = new ExpressionNode("NO");

    root.preOrder();
    return 0;
}
