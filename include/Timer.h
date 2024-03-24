

class Timer
{
    private:
    bool m_new_second;
    float m_current_time;
    float m_delta_time;
    float m_last_time;
    unsigned int m_frames;
    unsigned int m_frames_in_last_second;
    float m_last_second;
    public:
    Timer() = default;
    ~Timer() = default;
    void Update();
    bool IsNewSecond() const;
    unsigned int GetFramesInLastSecond() const;
    float GetDeltaTime() const;
};