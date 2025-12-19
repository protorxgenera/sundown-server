#pragma once

enum class ProtocolMessageType
{
    PairingRequest,
    PairingChallenge,
    PairingResponse,
    PairingAccepted,
    PairingRejected,

    StateRequest,
    StateSnapshot,
    StateUpdate,

    ScheduleShutdown,
    AbortShutdown,
    CommandAck,

    Error
};
