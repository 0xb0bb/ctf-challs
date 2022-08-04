package main

import (
	"encoding/json"
	"fmt"
	"github.com/tkanos/gonfig"
	"io/ioutil"
	"net/http"
	"net/url"
	"os"
)

const CONFIG_FILE = ".config.json"

type Conf struct {
	Url  string `env:"PWN_URL"`
	User string `env:"PWN_USER"`
	Pass string `env:"PWN_PASS"`
}

type Result struct {
	Status  string `json:"status"`
	Message string `json:"message"`
}

const winStr = `
██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗██╗
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║██║
 ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║██║
  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║╚═╝
   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║██╗
   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═╝
`

const loseStr = `
██╗   ██╗ ██████╗ ██╗   ██╗    ██╗      ██████╗ ███████╗███████╗██╗
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║     ██╔═══██╗██╔════╝██╔════╝██║
 ╚████╔╝ ██║   ██║██║   ██║    ██║     ██║   ██║███████╗█████╗  ██║
  ╚██╔╝  ██║   ██║██║   ██║    ██║     ██║   ██║╚════██║██╔══╝  ╚═╝
   ██║   ╚██████╔╝╚██████╔╝    ███████╗╚██████╔╝███████║███████╗██╗
   ╚═╝    ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝
`

func main() {

	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: %s <username>\n", os.Args[0])
		os.Exit(-1)
	}

	conf := Conf{}
	err := gonfig.GetConf(CONFIG_FILE, &conf)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: %s\n", err)
		os.Exit(-1)
	}

	client := &http.Client{}
	url := fmt.Sprintf("%s?token=%s", conf.Url, url.QueryEscape(os.Args[1]))

	req, _ := http.NewRequest(http.MethodGet, url, nil)
	req.SetBasicAuth(conf.User, conf.Pass)
	req.Header.Set("User-Agent", "Pwny-Racing-Submission-Client_v1")

	resp, err := client.Do(req)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: %s\n", err)
		os.Exit(-1)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: %s\n", err)
		os.Exit(-1)
	}

	result := Result{}
	json.Unmarshal(body, &result)

	switch result.Status {
	case "win":
		fmt.Println(winStr)
		if len(result.Message) > 0 {
			fmt.Println(result.Message)
		}
	case "lose":
		fmt.Println(loseStr)
		if len(result.Message) > 0 {
			fmt.Println(result.Message)
		}
	default:
		fmt.Fprintf(os.Stderr, "error: %s\n", result.Message)
		os.Exit(-1)
	}
}