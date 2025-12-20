#pragma once

// at any moment, the session is in exactly one state

enum class SessionState
{
    Connected,
    Pairing,
    Paired
};