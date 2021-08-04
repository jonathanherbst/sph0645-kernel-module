// SPDX-License-Identifier: GPL-2.0-only
/*
 * Driver for the PCM5102A codec
 *
 * Author:	Florian Meier <florian.meier@koalo.de>
 *		Copyright 2013
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <sound/soc.h>
#include <sound/soc-dai.h>

static struct snd_soc_dai_driver sph0645_dai = {
	.name = "sph0645-hifi",
	.capture = {
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.formats = SNDRV_PCM_FMTBIT_S32_BE,
		.rates = SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000;
	},
};

static struct snd_soc_component_driver soc_component_dev_sph0645 = {
	.idle_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
};

static int pcm5102a_probe(struct platform_device *pdev)
{
	return devm_snd_soc_register_component(&pdev->dev, &soc_component_dev_sph0645,
			&sph0645_dai, 1);
}

static const struct of_device_id sph0645_of_match[] = {
	{ .compatible = "sph0645", },
	{ }
};
MODULE_DEVICE_TABLE(of, sph0645_of_match);

static struct platform_driver sph0645_codec_driver = {
	.probe		= pcm5102a_probe,
	.driver		= {
		.name	= "sph0645-codec",
		.of_match_table = sph0645_of_match,
	},
};

module_platform_driver(sph0645_codec_driver);

MODULE_DESCRIPTION("ASoC SPH0645 codec driver");
MODULE_AUTHOR("Jonathan Herbst <amd64d@gmail.com>");
MODULE_LICENSE("GPL v2");
