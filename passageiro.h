#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

class Passageiro {
  public:
    int id() const { return id_; }
    bool bilhete_dourado() const { return bilhete_dourado_; }
  private:
    int id_;
    bool bilhete_dourado_;
};

#endif /* PASSAGEIRO_H_ */