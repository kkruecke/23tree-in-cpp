#include "include/test.h"
#include "include/tree23.h"
#include "include/level-order-display.h"
#include "include/debug-level-order-printer.h"
//#include "include/debug.h"
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void print_tree(const tree23<int, int>& tree)
{
  cout << flush << "Level order print of tree: ";

  levelOrderDisplay<tree23<int, int>> printFunctor(tree, cout);

  tree.levelOrderTraverse(printFunctor);
   
  cout << flush;

  cout << "\n\nIn order print of tree: ";
  
  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ' '; };
/*
  tree.inOrderTraverse(lambda_closure);
 */ 
    
  tree23<int, int>::const_iterator const_iter = tree.begin();
  
  for(const auto& key_value : tree) {
      
      cout << key_value.key << flush;
  }
  cout << endl;
}
 
void debug_print_tree(const tree23<int, int> & tree)
{
  cout << flush << "Level order print of tree: ";
  
  int depth = tree.getHeight();
  
  levelOrderDisplay<tree23<int, int>> printFunctor(tree, cout);

  tree.levelOrderTraverse(printFunctor);
   
  debug_levelOrderPrinter<tree23<int,int>> debugprintFunctor(tree, cout);

  cout << "\nLevel order debug print of tree: \n" << flush;
  
  tree.levelOrderTraverse(debugprintFunctor);
   
  cout << endl;

  cout << "\n\nIn order print of tree: ";

  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ' '; };

  tree.inOrderTraverse(lambda_closure);
  
  cout << endl << flush;
}

void run_tests(const std::vector<std::vector<int>>& other_cases, const std::vector<int>& base_case, void (*f)(const std::vector<int>&, int), int break_key)
{
   for( const auto& append_vec : other_cases) {

       vector<int> test_case {base_case};

       auto key_break = test_case.size();

       copy(append_vec.begin(), append_vec.end(), back_inserter(test_case));

       random_shuffle(test_case.begin(), test_case.end());
       
       cout << "Input vector<int> to next case is: \n";

       copy(test_case.begin(), test_case.end(), ostream_iterator<int>(cout, ", "));
              
       cout << endl << flush;
       
       try {
      
           (*f)(test_case, break_key);
      
       } catch(...) {

           cout << "An uncaught exception occured:\n"  << endl;
       }
       
       cout << "\n================================" << endl; 
  }

}

void test_insert(const vector<int>& v, int break_key)
{    
  tree23<int, int> tree;
  
   int i = 0;
    
   for (auto& key : v) {

      cout << "Inserting: " << key << std::endl;
      
      if (key == break_key) {
          
         int debug = 10;
         
         ++debug;
         
         tree.insert(key, key);
         
      } else {
          
         tree.insert(key, key);
      }

      print_tree(tree);  // or to print debug info change to: debug_print_tree(tree);      
      
    }

    cout << flush << "\nTesting find(v) of all keys v inserted so for. First, reprinting the tree.\n" << flush;

    print_tree(tree);  

    for (auto key : v) {
      
         string result_msg = tree.find(key) ? " found " : " not found ";
           
         cout << "Key " << key << " was " << result_msg << endl; 
    } 

    return; 
}

void test_remove(const std::vector<int>& input, int break_key) //, int break_key)
{  
   tree23<int, int> tree;

   int i = 0;
  
   for(auto& key : input) {

      int debug = 0;  // used only to set a breakpoint prior to insert call.
         
      tree.insert(key, ++i);

   }

   vector<int> removal_vec{input}; // make copy of input vector

   random_shuffle(removal_vec.begin(), removal_vec.end()); // and scramble it.
   
   cout << "Printing the tree before removals start.\n";
   
   debug_print_tree(tree);
   
   for(auto& key : removal_vec) {

       cout << "\nRemoving key: " << key << endl;
       
       if (key == 37) {  //after removing 37, tree has many nullptrs still in it. Then blowes up when 150 removed.

          auto debug = 10;
          ++debug;
          tree.remove(key);
         
       } else {
          
          tree.remove(key);
       }
       cout << "\nPrinting tree in order after removal: \n";
               
       debug_print_tree(tree);   // to do regular print do: print_tree(tree);
    }
       
    cout << flush << "\nTesting find(v) of all keys v removed so for. First, reprinting the tree.\n" << flush;

    print_tree(tree);  

    for (auto& key : removal_vec) {
      
         string result_msg = tree.find(key) ? " found " : " not found ";
           
         cout << "Key " << key << " was " << result_msg << endl; 
    } 
}

void test_copy_ctor(const std::vector<int>& input, int break_key) 
{
  tree23<int, int> tree;

  int i = 0;
  
  for(auto& key : input) {

     int debug = 0;  
         
     tree.insert(key, ++i);
  }

  tree23<int, int> tree_copy{tree};
  
  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ", "; };
  
  cout << "input tree first followed by its copy" << endl;

  tree.inOrderTraverse(lambda_closure);
  
  cout << "\n";
}

void test_iterator_base(const std::vector<int>& input, int break_key) 
{
  tree23<int, int> tree;
  
   int i = 0;
    
   for (auto& key : input) {

      cout << "Inserting: " << key << std::endl;
      
      if (key == break_key) {
          
         int debug = 10;
         
         ++debug;
         
         tree.insert(key, key);
         
      } else {
          
         tree.insert(key, key);
      }
    }

  cout << "Level order print of tree: \n";

  levelOrderDisplay<tree23<int, int>> printFunctor(tree, cout);

  tree.levelOrderTraverse(printFunctor);
  
  cout << "\n\nIn order print of tree with tree23<int, int>::traverse(F):\n";
  
  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ", "; };

  tree.inOrderTraverse(lambda_closure);
  
  cout << flush << "\nPrinting tree with external iterator:\n";

  try {

    print_with_iterator_base(tree);

  } catch (std::exception& e) {

    cout << "\nException: " << e.what() << endl; 
  }

  cout << flush; 
  return; 
}


void test_forward_iterator(const std::vector<int>& input, int break_key) 
{
  tree23<int, int> tree;
  
   int i = 0;
    
   for (auto& key : input) {

      cout << "Inserting: " << key << std::endl;
      
      if (key == break_key) {
          
         int debug = 10;
         
         ++debug;
         
         tree.insert(key, key);
         
      } else {
          
         tree.insert(key, key);
      }
    }

  cout << "Level order print of tree: \n";

  levelOrderDisplay<tree23<int, int>> printFunctor(tree, cout);

  tree.levelOrderTraverse(printFunctor);
  
  cout << "\n\nIn order print of tree:\n";
  
  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ", "; };

  tree.inOrderTraverse(lambda_closure);
  
  cout << flush << "\nPrinting tree with iterator:\n";

  try {

    print_with_forward_iterator(tree);

  } catch (std::exception& e) {

    cout << "\nException: " << e.what() << endl; 
  }

  cout << flush; 
  return; 
}

void print_with_forward_iterator(const tree23<int, int>& tree)
{ 
  auto citer = tree.begin();
  auto cend_iter = tree.end();

  for( ; citer != cend_iter; ++citer) {

       cout << (*citer).key << ", ";
       cout << flush;
  } 
}

void print_with_iterator_base(const tree23<int, int>& tree)
{ 
  tree23<int, int>& non_const_tree = const_cast<tree23<int, int>&>(tree);

  tree23<int, int>::iterator_base start{non_const_tree, tree23<int, int>::iterator_position::beg};   //<-- Compile errors start when this is uncommented.
  
  tree23<int, int>::iterator_base end{non_const_tree, tree23<int, int>::iterator_position::end};

  for( ; start != end; ) {

       tree23<int, int>::KeyValue& key_value = start.dereference();

       cout << key_value.key << ", " << flush;

       start.increment();
  } 

  cout << endl << flush;
}


void test_backward_iterator(const std::vector<int>& input, int break_key) 
{
  tree23<int, int> tree;
  
   int i = 0;
    
   for (auto& key : input) {

      cout << "Inserting: " << key << std::endl;
      
      if (key == break_key) {
          
         int debug = 10;
         
         ++debug;
         
         tree.insert(key, key);
         
      } else {
          
         tree.insert(key, key);
      }
    }

  cout << "Level order print of tree: \n";

  levelOrderDisplay<tree23<int, int>> printFunctor(tree, cout);

  tree.levelOrderTraverse(printFunctor);
  
  cout << "\n\nIn order print of tree:\n";
  
  auto lambda_closure = [](const tree23<int, int>::KeyValue& key_value ){ cout << key_value.key << ", "; };

  tree.inOrderTraverse(lambda_closure);
  
  cout << flush << "\nPrinting tree with iterator:\n";
  try {

    print_with_backward_iterator(tree);

  } catch (std::exception& e) {

    cout << "\nException: " << e.what() << endl; 
  }

  cout << flush; 
  return; 
}

void print_with_backward_iterator(const tree23<int, int>& tree)
{
 
  tree23<int, int>::const_reverse_iterator criter = tree.rbegin();
  tree23<int, int>::const_reverse_iterator crend_iter = tree.rend();

  for( ; criter != crend_iter; ++criter) {

       const tree23<int, int>::KeyValue& key_value = *criter;

       cout << key_value.key << ", " << flush;
  } 
}
