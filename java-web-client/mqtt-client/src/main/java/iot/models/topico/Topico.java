package iot.models.topico;

/**
 * Created by bruno on 09/07/17.
 */
public class Topico {
    public String identificador;
    public Integer valor;

    public Topico() {}
    public Topico(String identificador, Integer valor) {
        this.identificador = identificador;
        this.valor = valor;
    }

    public String getIdentificador() {
        return identificador;
    }

    public void setIdentificador(String identificador) {
        this.identificador = identificador;
    }

    public Integer getValor() {
        return valor;
    }

    public void setValor(Integer valor) {
        this.valor = valor;
    }
}
