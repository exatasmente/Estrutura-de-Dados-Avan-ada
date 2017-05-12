
/**
 *
 * @author Luiz Neto
 */
public class Main {
    
     public static void main(String[] args)
    {
        Arvore test = new Arvore();
 
        
        test.inserir(50);
        test.inserir(30);
        test.inserir(20);
        test.inserir(40);
        test.inserir(70);
        test.inserir(60);
        test.inserir(80);
        test.inserir(10);
 
        System.out.println("Percorrendo em InOrdem");
        test.inOrdem();
        System.out.println();
        System.out.println("Percorrendo em PreOrdem");
        test.preOrdem();
        System.out.println();
        System.out.println("Percorrendo em PosOrdem");
        test.posOrdem();
        System.out.println();
        System.out.println(test.busca(40));
        
 
    
    }
}