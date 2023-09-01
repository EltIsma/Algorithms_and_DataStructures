import java.util.Scanner;

public class BST {
     static class Node{
        int key;
        Node left;
        Node right;
        Node parent;
        
    }
    static class BinTree{
        Node root;
    }

    Node min(Node node) {
        if (node.left == null) {
          return node;
        }
        return min(node.left);
    }

    static void Insert(BinTree tree, Node node) {
        Node y = null;
        Node x = tree.root;
        while (x != null) {
          y = x;
          if (node.key < x.key) {
            x = x.left;
          } else if (node.key == x.key) {
            return;
          } else {
            x = x.right;
          }
        }
        node.parent = y;
        if (y == null) {
          tree.root = node;
        } else if (node.key < y.key) {
          y.left = node;
        } else {
          y.right = node;
        }
    }
    static void inorder(Node Root){
        if (Root != null) {
            inorder(Root.left);
            System.out.print(" " + Root.key);
            inorder(Root.right);
        }
    }

    static void emptyBST(Node root){
      if (root != null) {
        emptyBST(root.left);
        emptyBST(root.right);
        root=null;
      }
    }

    void Transplant(BinTree tree, Node first, Node second) {
      if (first.parent == null) {
        tree.root = second;
      } else if (first == first.parent.left) {
        first.parent.left = second;
      } else {
        first.parent.right = second;
      }
      if (second != null) {
        second.parent = first.parent;
      }
    }

    void Erase(BinTree tree, Node node) {
      if (node.left == null) {
        Transplant(tree, node, node.right);
      } else if (node.right == null) {
        Transplant(tree, node, node.left);
      } else {
        Node y = min(node.right);
        if (y.parent != node) {
          Transplant(tree, y, y.right);
          y.right = node.right;
          y.right.parent = y;
        }
        Transplant(tree, node, y);
        y.left = node.left;
        y.left.parent = y;
      }
      
    }

    static int height(Node node)
    {
        if (node == null)
            return 0;
        else {
            int lDepth = height(node.left);
            int rDepth = height(node.right);
            if (lDepth > rDepth)
                return (lDepth + 1);
            else
                return (rDepth + 1);
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BinTree tree = new BinTree();
        tree.root = null;
        int key = 0;
        key=in.nextInt();
        while (key != 0) {
        Node node = new Node();
        node.left = null;
        node.right = null;
        node.key = key;
        Insert(tree,node);
        key=in.nextInt();
        }
        inorder(tree.root);
        in.close();
    }
 


}
