# Asysnc package (BETA, UNIX)
This packages enables multi-threading in msh. The stage is rather BETA and there may still be BUGS.
This package uses the pthread.h library, which may not exist everywhere and cause errors when cross-compiling.
If you want to use this package please set "MULTI_THREAD" in mshgit in "dependencies/std.h" to "1".

## commands

### async()
Use this command instead of the std-essential command "call()" to start a function in another thread.
Example:

    func() message(msg)
        // do something
    funcEnd()

    x = async() message(Hi I run in async)

The returned value is the ID of the thread generated, which is used in await()

### await
Wait for a thread / a function called with "async()" to finish.
Example from before:

    await() x()
    // there are no other threads open now

