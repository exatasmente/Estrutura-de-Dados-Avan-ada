
/**
 *
 * @author Luiz Neto
 */
public class Node {

    private int valor;
    private Node direita;
    private Node esquerda;
    private int altura;    

    public Node(int valor) {
        this.valor = valor;
        this.altura();
    }

    public Node(int valor, Node direita, Node esquerda) {
        this.valor = valor;
        this.direita = direita;
        this.esquerda = esquerda;
    }

    public int getAltura() {
		return altura;
	}

	public void setAltura(int altura) {
		this.altura = altura;
	}

	public int getValor() {
        return this.valor;
    }

    public void setValor(int valor) {
        this.valor = valor;
    }

    public Node getDireita() {
        return this.direita;
    }

    public void setDireita(Node direita) {
        this.direita = direita;
    }

    public Node getEsquerda() {
        return this.esquerda;
    }

    public void setEsquerda(Node esquerda) {
        this.esquerda = esquerda;
    }

    public void altura() {
      if(this.direita == null && this.esquerda == null){
    	  this.setAltura(1);
      }else{
    	  if(this.esquerda.getValor() > this.direita.getValor()){
    		  this.esquerda.setAltura(this.getAltura()+1);
    	  }else{
    		  this.direita.setAltura(this.getAltura()+1);
    	  }
      }
    }

    public boolean busca(int valor) {

        if (valor == this.valor) {
            return true;
        } else if (valor < this.valor) {

            if (this.esquerda == null) {
                return false;
            } else {
                return this.esquerda.busca(valor);
            }

        } else if (valor > this.valor) {

            if (this.direita == null) {
                return false;
            } else {
                return this.direita.busca(valor);
            }

        }

        return false;

    }

    @Override
    public String toString() {
        return "No Valor:" + this.getValor() + "\n No direita: " + this.getDireita() + "\n No Esqureda: " + this.getEsquerda() + "";
    }

}