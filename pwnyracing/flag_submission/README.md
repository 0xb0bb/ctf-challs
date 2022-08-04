# pwny.race Submission Client

### Building

Build with the command `go build client.go`. The only dependency that is required is
the `gonfig` library. To install this simply type `go get github.com/tkanos/gonfig`.

A static binary will be built that can be used without modification for each event.

### Configuration

The client expects a local file called `.config.json` to exist that will contain the
data to configure the client. As a fallback (and for testing and use in challenges
with a different format) environmental variables can be used to configure the client.

The fields the client expects at a minimum are:

	* `url`  - `URL` to service the submission request.
	* `user` - `HTTP_AUTH` required to authenticate.
	* `pass` - `HTTP_AUTH` required to authenticate.

The corresponding names for the environmental variables are:

	* `PWN_URL`
	* `PWN_USER`
	* `PWN_PASS`

If both the configuration file and environmental variables are present, the environmental
variables will take precedence.

An example of a valid configuration file would be:
```json
{
	"url":  "https://pwny.racing/example",
	"user": "pwn",
	"pass": "s3cREtz"
}
```

### Running

The client is meant to be run with a single argument. This argument will be an identifying
token for the user on the server side. The server side logic will be responsible for any
verification and return an applicable status code and json response. Anything that is not
recognised explicitly by this client will cause a simple error printed to the user.

There are three states of the application output:

1. YOU WIN!
2. YOU LOSE!
3. Error message.

### Server

The server has two requirements.

1. Implement `HTTP BASIC AUTH` using the configured username and password.
2. Return a valid `json` response with an object containing `status` and `message` fields.

The `status` field of the `json` response has three states:
1. `win`
2. `lose`
3. `error`

Any unrecognised `status` is treated as an error.

If the `message` field of the `json` response is not empty then it will be printed to the user (this is useful for printing more descriptive error messages).

An example of a valid `json` response is:
```json
{
	"status": "win",
	"message": "Congratulations b0bb! You have won episode 1 of pwny race.",
}
```

The identifying information the user will provide in the first argument when running the client will be present in the `token` `GET` parameter of the request.

## Author

[b0bb](https://twitter.com/0xb0bb)
