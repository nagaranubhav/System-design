#include <iostream>
#include <string>

using namespace std;

// Base class
class ModelTrainer {
public:

    // Template Method
    // Yeh pura pipeline ka FIXED FLOW define karta hai
    // Subclasses is order ko change nahi kar sakte
    void trainPipeline(const string& dataPath) {

        // Step 1: Common step
        loadData(dataPath);

        // Step 2: Default step (override ho sakta hai)
        preprocessData();

        // Step 3: Abstract → subclass implement karega
        trainModel();

        // Step 4: Abstract → subclass implement karega
        evaluateModel();

        // Step 5: Default step (override optional)
        saveModel();
    }

protected:

    // Common logic sabke liye same
    void loadData(const string& path) {
        cout << "[Common] Loading dataset from " << path << "\n";
    }

    // Default implementation (hook method)
    virtual void preprocessData() {
        cout << "[Common] Splitting into train/test and normalizing\n";
    }

    // Pure virtual → MUST override
    virtual void trainModel() = 0;

    // Pure virtual → MUST override
    virtual void evaluateModel() = 0;

    // Default implementation (optional override)
    virtual void saveModel() {
        cout << "[Common] Saving model to disk as default format\n";
    }
};

// Neural Network subclass
class NeuralNetworkTrainer : public ModelTrainer {
protected:

    // Custom training logic
    void trainModel() override {
        cout << "[NeuralNet] Training Neural Network for 100 epochs\n";
    }

    // Custom evaluation
    void evaluateModel() override {
        cout << "[NeuralNet] Evaluating accuracy and loss on validation set\n";
    }

    // Override save behavior
    void saveModel() override {
        cout << "[NeuralNet] Serializing network weights to .h5 file\n";
    }
};

// Decision Tree subclass
class DecisionTreeTrainer : public ModelTrainer {
protected:

    // Uses default preprocessData()

    void trainModel() override {
        cout << "[DecisionTree] Building decision tree with max_depth=5\n";
    }

    void evaluateModel() override {
        cout << "[DecisionTree] Computing classification report (precision/recall)\n";
    }

    // saveModel not overridden → default use hoga
};

// MAIN FUNCTION DRY RUN
int main() {

    cout << "=== Neural Network Training ===\n";

    // Polymorphism
    ModelTrainer* nnTrainer = new NeuralNetworkTrainer();

    // Call Template Method
    nnTrainer->trainPipeline("data/images/");

    cout << "\n=== Decision Tree Training ===\n";

    ModelTrainer* dtTrainer = new DecisionTreeTrainer();

    dtTrainer->trainPipeline("data/iris.csv");

    return 0;
}

/*
───────────────────────────────────────────────────────────
TOP-NOTCH DRY RUN (STEP BY STEP FLOW)
───────────────────────────────────────────────────────────

CASE 1: Neural Network

Call:
nnTrainer->trainPipeline("data/images/");

STEP 1:
loadData("data/images/")
OUTPUT:
[Common] Loading dataset from data/images/

STEP 2:
preprocessData() → base class version
OUTPUT:
[Common] Splitting into train/test and normalizing

STEP 3:
trainModel() → NeuralNetworkTrainer version
OUTPUT:
[NeuralNet] Training Neural Network for 100 epochs

STEP 4:
evaluateModel() → NeuralNetworkTrainer version
OUTPUT:
[NeuralNet] Evaluating accuracy and loss on validation set

STEP 5:
saveModel() → overridden version
OUTPUT:
[NeuralNet] Serializing network weights to .h5 file

───────────────────────────────────────────────────────────
CASE 2: Decision Tree

Call:
dtTrainer->trainPipeline("data/iris.csv");

STEP 1:
loadData("data/iris.csv")
OUTPUT:
[Common] Loading dataset from data/iris.csv

STEP 2:
preprocessData() → base class version
OUTPUT:
[Common] Splitting into train/test and normalizing

STEP 3:
trainModel() → DecisionTreeTrainer version
OUTPUT:
[DecisionTree] Building decision tree with max_depth=5

STEP 4:
evaluateModel() → DecisionTreeTrainer version
OUTPUT:
[DecisionTree] Computing classification report (precision/recall)

STEP 5:
saveModel() → base class version (NOT overridden)
OUTPUT:
[Common] Saving model to disk as default format

───────────────────────────────────────────────────────────
KEY OBSERVATIONS (VERY IMPORTANT)

1. Flow is FIXED
   subclasses sequence change nahi kar sakte

2. Runtime Polymorphism
   pointer base class ka hai
   object subclass ka hai

3. Dynamic Binding
   trainModel(), evaluateModel() runtime pe decide hote

4. Hooks vs Abstract
   preprocessData() → optional override
   trainModel() → mandatory override

───────────────────────────────────────────────────────────
EDGE CASE THINKING (INTERVIEW LEVEL)

Q: Agar subclass trainModel implement na kare?
A: Compile-time error (pure virtual)

Q: Agar template method virtual hota?
A: Subclass pura flow tod sakta → BAD DESIGN

Q: Agar bahut variations ho jaye?
A: Pattern break hone lagega → Strategy Pattern better

───────────────────────────────────────────────────────────