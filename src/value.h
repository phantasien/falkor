namespace moonchild {

class Value {

  public:
    static enum Type {NUMBER, STRING};

    Value(Type type);

  private:
    Type type_;

};

}