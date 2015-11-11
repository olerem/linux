/*
 * Copyright (C) 2015-1016 Alban Bedel <albeu@free.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/phy/phy.h>

static const struct of_device_id simple_phy_of_match[] = {
	{ .compatible = "simple-phy", },
	{}
};
MODULE_DEVICE_TABLE(of, simple_phy_of_match);

static int simple_phy_probe(struct platform_device *pdev)
{
	struct phy *phy;

	phy = devm_phy_create(&pdev->dev, NULL, NULL);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	return PTR_ERR_OR_ZERO(devm_of_phy_provider_register(
				&pdev->dev, of_phy_simple_xlate));
}

static struct platform_driver simple_phy_driver = {
	.probe	= simple_phy_probe,
	.driver = {
		.of_match_table	= of_match_ptr(simple_phy_of_match),
		.name		= "phy-simple",
	}
};
module_platform_driver(simple_phy_driver);

MODULE_DESCRIPTION("Simple PHY driver");
MODULE_AUTHOR("Alban Bedel <albeu@free.fr>");
MODULE_LICENSE("GPL");
