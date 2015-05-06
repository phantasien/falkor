namespace mnc {

class Value {

  public:
    enum Type {NUMBER, STRING};

    Value(Type type);

  private:
    Type type_;

};

}