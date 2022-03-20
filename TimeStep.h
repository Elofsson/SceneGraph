#pragma once

class TimeStep
{
public:
  TimeStep(float timeStep = 0.0f) : m_time(timeStep){}

  operator float () const { return m_time; }

  float getSeconds() { return m_time; }
  float getMilliSeconds() { return m_time * 1000.0f; }

private:
  float m_time;
};