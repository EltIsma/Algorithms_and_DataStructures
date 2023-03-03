public class Stack<T>{

    private Node<T> head;
    private static class Node<T>{
        private final T value;
        private Node<T> next;
        private Node(T value){this.value=value;}

    }

    public T peek(){
        return head.value;
    }

    public T pop(){
        T value=head.value;
        head=head.next;
        return value;

    }
    public void push(T t){
        Node<T> node=new Node<>(t);
        node.next=head;
        head=node;
       
    }

    public boolean isEmpty(){
        return head==null;
    }

    public static void main(String[] args) {
        Stack<Integer> sll = new Stack<>();
 
        sll.push(10);
        sll.push(20);
        sll.push(30);
    }
}
