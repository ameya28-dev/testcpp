class Random {
   public:
    Random(const Random& other) = delete;

    static Random& Get() {
        static Random instance;
        return instance;
    }

    static float Float() { return Get().FloatImpl(); }

   private:
    Random() {};

    float FloatImpl() { return random_number; }

    float random_number = 0.5f;
};

int main() {
    Random& instance = Random::Get();
    auto number = Random::Float();
    auto num = instance.Float();
}